// Создание потоков-читателей
    std::vector<std::thread> readers;
    int num_readers = 3;
    for (int i = 0; i < num_readers; ++i) {
        readers.push_back(std::thread(reader_thread, std::ref(cache), i + 1, 8));
    }

    // Запуск с detach
    for (auto& w : writers) {
        w.detach();
    }
    for (auto& r : readers) {
        r.detach();
    }

    // Периодический вывод содержимого кэша
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cache.print_all();
    }

    cache.stop();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "\n=== Финальное состояние кэша ===" << std::endl;
    cache.print_all();

    return 0;
}
