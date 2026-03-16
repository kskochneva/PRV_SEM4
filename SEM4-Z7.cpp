void consumer_thread(PriorityQueue<std::string>& queue, int id, int num_items) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> delay_dist(200, 600);

    int consumed = 0;
    while (consumed < num_items) {
        std::string value = queue.pop();
        if (value.empty() && queue.empty()) break;

        if (!value.empty()) {
            consumed++;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));
    }
    std::cout << "Потребитель " << id << " завершил работу (потреблено: " << consumed << ")" << std::endl;
}

int main() {
    PriorityQueue<std::string> pq;

    std::cout << "=== Многопоточная очередь с приоритетом ===" << std::endl;

    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;
    const int ITEMS_PER_PRODUCER = 8;
    const int TOTAL_ITEMS = NUM_PRODUCERS * ITEMS_PER_PRODUCER;

    std::cout << "Производителей: " << NUM_PRODUCERS << " (по " << ITEMS_PER_PRODUCER << " элементов)" << std::endl;
    std::cout << "Потребителей: " << NUM_CONSUMERS << std::endl;
    std::cout << "Всего элементов: " << TOTAL_ITEMS << "\n" << std::endl;

    // Создание потоков-производителей
    std::vector<std::thread> producers;
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.push_back(std::thread(producer_thread, std::ref(pq), i + 1, ITEMS_PER_PRODUCER));
    }

    // Создание потоков-потребителей
    std::vector<std::thread> consumers;
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.push_back(std::thread(consumer_thread, std::ref(pq), i + 1, TOTAL_ITEMS / NUM_CONSUMERS));
    }

    // Запуск с detach
    for (auto& p : producers) {
        p.detach();
    }
    for (auto& c : consumers) {
        c.detach();
    }

    // Мониторинг состояния очереди
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\n[Мониторинг] Размер очереди: " << pq.size() << std::endl;
    }

    pq.stop();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "\n=== Финальное состояние очереди ===" << std::endl;
    std::cout << "Размер очереди: " << pq.size() << std::endl;

    return 0;
}
