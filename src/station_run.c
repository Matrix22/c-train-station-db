#include "./include/station.h"

/**
 * @brief Function to check the arrive_train program
 * 
 */
void test_arrive_train(void) {
    FILE *fin = fopen("out/output_arrive_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }

    train_station_t *station = open_train_station(5);
    show_existing_trains(station, fin);
    
    arrive_train(station, 2, 19);
    show_existing_trains(station, fin);
    
    arrive_train(station, 3, 100);
    show_existing_trains(station, fin);
    
    arrive_train(station, 3, 10);
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    station = open_train_station(100);
    
    for (int32_t iter = -2; iter < 102; ++iter) {
        arrive_train(station, iter, 1);
    }
    
    for (int32_t iter = 102; iter < -1; --iter) {
        arrive_train(station, iter, 2);
    }
    
    show_existing_trains(station, fin);
    close_train_station(station);
    
    station = NULL;
    show_existing_trains(station, fin);
    
    fclose(fin);
}

/**
 * @brief Function to check the leave_train function
 * 
 */
void test_leave_train(void) {
    FILE *fin = fopen("out/output_leave_train.out", "w");

    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }

    train_station_t *station = open_train_station(50);
    
    arrive_train(station, 5, 20);
    arrive_train(station, 4, 10);
    arrive_train(station, 0, 0);
    arrive_train(station, 3, 1);
    show_existing_trains(station, fin);
    
    for (int32_t iter = -2; iter < 102; ++iter) {
        leave_train(station, iter);
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 100; ++iter) {
        arrive_train(station, iter, 1);
    }
    
    for (int32_t iter = 0; iter < 100; iter +=2) {
        leave_train(station, iter);
    }
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the add_train_program
 * 
 */
void test_add_train_wagon(void) {
    FILE *fin = fopen("out/output_add_train_wagon.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(5);
    
    arrive_train(station, 0, 100);
    arrive_train(station, 2, 200);
    arrive_train(station, 4, 300);
    
    show_existing_trains(station, fin);
    
    add_train_wagon(station, -1, 0);
    add_train_wagon(station, 0, 1);
    add_train_wagon(station, 1, 2);
    add_train_wagon(station, 2, 3);
    add_train_wagon(station, 3, 4);
    add_train_wagon(station, 4, 5);
    add_train_wagon(station, 5, 6);
    add_train_wagon(station, 0, 1);
    add_train_wagon(station, 1, 2);
    add_train_wagon(station, 2, 3);
    add_train_wagon(station, 3, 4);
    add_train_wagon(station, 4, 5);
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 100; ++iter) {
        add_train_wagon(station, 0, 17);
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 100; ++iter) {
        add_train_wagon(station, 2, 19);
        add_train_wagon(station, 4, 23);
    }
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the remove_train_wagons
 * 
 */
void test_remove_train_wagons(void) {
    FILE *fin = fopen("out/output_remove_train_wagons.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    
    }
    
    train_station_t *station = open_train_station(8);
    
    arrive_train(station, 1, 100);
    arrive_train(station, 3, 300);
    arrive_train(station, 4, 4000);
    arrive_train(station, 7, 70);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 1, 1);
    add_train_wagon(station, 3, 2);
    add_train_wagon(station, 3, 2);
    add_train_wagon(station, 4, 3);
    add_train_wagon(station, 4, 2);
    add_train_wagon(station, 4, 3);
    add_train_wagon(station, 7, 4);
    add_train_wagon(station, 7, 1);
    add_train_wagon(station, 7, 4);
    add_train_wagon(station, 7, 1);
    add_train_wagon(station, 7, 4);
    show_existing_trains(station, fin);
    
    remove_train_wagons(station, 1, 1);
    remove_train_wagons(station, 3, 2);
    remove_train_wagons(station, 4, 3);
    remove_train_wagons(station, 7, 4);
    show_existing_trains(station, fin);
    
    for (int32_t iter = -2; iter < 10; ++iter) {
        remove_train_wagons(station, iter, 1);
        remove_train_wagons(station, iter, 2);
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter_i = 0; iter_i < 50; ++iter_i) {
        for (int32_t iter_j = 0; iter_j < 8; ++iter_j) {
            arrive_train(station, iter_j, 100);
            add_train_wagon(station, iter_j, 7);
            add_train_wagon(station, iter_j, 7);
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter_i = 0; iter_i < 50; ++iter_i) {
        for (int32_t iter_j = 0; iter_j < 8; ++iter_j) {
            remove_train_wagons(station, iter_j, 7);
        }
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter_i = 50; iter_i > -2; --iter_i) {
        for (int32_t iter_j = 0; iter_j < 5; ++iter_j) {
            remove_train_wagons(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    
    leave_train(station, 5);
    leave_train(station, 6);
    leave_train(station, 7);
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the move_train_wagons
 * 
 */
void test_move_train_wagons(void) {
    FILE *fin = fopen("out/output_move_train_wagons.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(3);
    
    arrive_train(station, 0, 100);
    arrive_train(station, 1, 100);
    arrive_train(station, 2, 100);
    
    for (int32_t iter = 1; iter <= 10; ++iter) {
        add_train_wagon(station, 2, iter);
        add_train_wagon(station, 0, iter);
    }
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 0, 4, 1, 2, 2);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 2, 1, 1, 0, 1);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 2, 1, 1, 1, 1);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 0, 10, 1, 1, 2);
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    station = open_train_station(10);
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, 100);
    }
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 9; ++iter_j) {
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 0, 1, 3, 1, 11);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 1, 11, 3, 2, 1);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 2, 2, 9, 3, 3);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 4, 1, 12, 5, 1);
    move_train_wagons(station, 4, 1, 10, 5, 0);
    move_train_wagons(station, 4, 1, 3, 5, 12);
    move_train_wagons(station, 4, 8, 3, 5, 10);
    move_train_wagons(station, 6, 9, 3, 7, 5);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 6, 1, 10, 7, 11);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 7, 1, 10, 6, 11);
    move_train_wagons(station, 8, 1, 10, 6, 1);
    move_train_wagons(station, 7, 10, 10, 9, 1);
    add_train_wagon(station, 9, 10);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 3, 3, 0, 2, 2);
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        leave_train(station, iter);
    }
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the find_express_train
 * 
 */
void test_find_express_train(void) {
    FILE *fin = fopen("out/output_find_express_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(10);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, 100);
    }
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 10; ++iter_j) {
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        remove_train_wagons(station, iter, iter + 1);
        fprintf(fin, "%d\n", find_express_train(station));
    }
    
    leave_train(station, 1);
    leave_train(station, 9);
    fprintf(fin, "%d\n", find_express_train(station));
    
    arrive_train(station, 1, 100);
    fprintf(fin, "%d\n", find_express_train(station));
    
    add_train_wagon(station, 1, 99);
    fprintf(fin, "%d\n", find_express_train(station));
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    station = open_train_station(10);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, iter * 10);
    }
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 10; ++iter_j) {
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    fprintf(fin, "%d\n", find_express_train(station));
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the find_overload_train
 * 
 */
void test_find_overload_train(void) {
    FILE *fin = fopen("out/output_find_overload_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(10);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, 100 - iter);
    }
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 10; ++iter_j) {
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    fprintf(fin, "%d\n", find_overload_train(station));
    
    for (int32_t iter = 9; iter >= 0; --iter) {
        remove_train_wagons(station, iter, 10 - iter);
        fprintf(fin, "%d\n", find_overload_train(station));
    }
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 9, 1, 9, 0, 1);
    move_train_wagons(station, 8, 1, 9, 1, 1);
    fprintf(fin, "%d\n", find_overload_train(station));
    
    move_train_wagons(station, 2, 1, 9, 7, 1);
    fprintf(fin, "%d\n", find_overload_train(station));
    
    remove_train_wagons(station, 7, 10);
    add_train_wagon(station, 5, 50);
    fprintf(fin, "%d\n", find_overload_train(station));
    
    leave_train(station, 5);
    add_train_wagon(station, 1, 1);
    fprintf(fin, "%d\n", find_overload_train(station));
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the find_optimal_train
 * 
 */
void test_find_optimal_train(void) {
    FILE *fin = fopen("out/output_find_optimal_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(10);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, 100 - iter);
    }
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 10; ++iter_j) {
            add_train_wagon(station, iter_j, iter_i);
        }
    }
    show_existing_trains(station, fin);
    fprintf(fin, "%d\n", find_optimal_train(station));
    
    for (int32_t iter = 9; iter >= 0; --iter) {
        remove_train_wagons(station, iter, 10);
        fprintf(fin, "%d\n", find_optimal_train(station));
    }
    
    leave_train(station, 1);
    leave_train(station, 9);
    fprintf(fin, "%d\n", find_optimal_train(station));
    
    arrive_train(station, 1, 100);
    fprintf(fin, "%d\n", find_optimal_train(station));
    
    add_train_wagon(station, 1, 99);
    fprintf(fin, "%d\n", find_optimal_train(station));
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the find_heaviest_sequence_train
 * 
 */
void test_find_heaviest_sequence_train(void) {
    FILE *fin = fopen("out/output_find_heaviest_sequence_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_wagon_t *wagon = NULL;
    train_station_t *station = open_train_station(10);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        arrive_train(station, iter, 1000);
    }
    
    int32_t platform = find_heaviest_sequence_train(station, 1, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    for (int32_t iter_i = 1; iter_i <= 10; ++iter_i) {
        for(int32_t iter_j = 0; iter_j < 10; ++iter_j) {
            add_train_wagon(station, iter_j, 1);
        }
    }
    
    add_train_wagon(station, 3, 2);
    platform = find_heaviest_sequence_train(station, 1, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    add_train_wagon(station, 7, 3);
    platform = find_heaviest_sequence_train(station, 1, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    add_train_wagon(station, 3, 4);
    platform = find_heaviest_sequence_train(station, 1, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 20, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 2, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 3, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 12, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        remove_train_wagons(station, iter, 1);
    }
    
    leave_train(station, 4);
    leave_train(station, 5);
    leave_train(station, 6);
    add_train_wagon(station, 3, 3);
    add_train_wagon(station, 3, 5);
    add_train_wagon(station, 3, 2);
    add_train_wagon(station, 3, 3);
    add_train_wagon(station, 7, 1);
    add_train_wagon(station, 7, 6);
    add_train_wagon(station, 7, 1);
    platform = find_heaviest_sequence_train(station, 2, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 3, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    add_train_wagon(station, 1, 1);
    add_train_wagon(station, 1, 4);
    add_train_wagon(station, 1, 4);
    add_train_wagon(station, 1, 4);
    add_train_wagon(station, 1, 1);
    remove_train_wagons(station, 3, 4);
    platform = find_heaviest_sequence_train(station, 3, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    remove_train_wagons(station, 1, 4);
    remove_train_wagons(station, 3, 5);
    add_train_wagon(station, 3, 1);
    platform = find_heaviest_sequence_train(station, 3, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 4, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    platform = find_heaviest_sequence_train(station, 5, &wagon);
    fprintf(fin, "%d %d\n", platform, wagon ? wagon->weight : -1);
    
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the order_train
 * 
 */
void test_order_train(void) {
    FILE *fin = fopen("out/output_order_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    
    }
    
    train_station_t *station = open_train_station(1);
    
    arrive_train(station, 0, 789);
    add_train_wagon(station, 0, 1);
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 0, 5);
    show_existing_trains(station, fin);
    
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 0, 3);
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 0, 2);
    add_train_wagon(station, 0, 4);
    add_train_wagon(station, 0, 6);
    add_train_wagon(station, 0, 4);
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    order_train(station, 0);
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    leave_train(station, 0);
    arrive_train(station, 0, 789);
    
    for (int32_t iter = 0; iter < 10; ++iter) {
        add_train_wagon(station, 0, 1);
        add_train_wagon(station, 0, 1);
        add_train_wagon(station, 0, iter + 2);
        add_train_wagon(station, 0, iter + 3);
    }
    
    add_train_wagon(station, 0, 1);
    add_train_wagon(station, 0, 1);
    show_existing_trains(station, fin);
    
    order_train(station, 0);
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Function to check the fix_overload_train
 * 
 */
void test_fix_overload_train(void) {
    FILE *fin = fopen("out/output_fix_overload_train.out", "w");
    
    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    train_station_t *station = open_train_station(4);
    
    for (int32_t iter = 0; iter < 4; ++iter) {
        arrive_train(station, iter, 10);
    }
    
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    for (int32_t iter = 1; iter < 5; ++iter) {
        add_train_wagon(station, 0, iter);
        add_train_wagon(station, 1, iter);
        add_train_wagon(station, 2, iter);
    }
    
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 1, 0);
    add_train_wagon(station, 1, 5);
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    remove_train_wagons(station, 1, 4);
    add_train_wagon(station, 1, 5);
    show_existing_trains(station, fin);
    
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    remove_train_wagons(station, 1, 5);
    add_train_wagon(station, 1, 6);
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    add_train_wagon(station, 1, 4);
    add_train_wagon(station, 1, 4);
    remove_train_wagons(station, 1, 6);
    remove_train_wagons(station, 1, 0);
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    move_train_wagons(station, 0, 1, 2, 1, 3);
    move_train_wagons(station, 1, 2, 1, 2, 2);
    show_existing_trains(station, fin);
    
    leave_train(station, 2);
    add_train_wagon(station, 1, 5);
    fix_overload_train(station);
    show_existing_trains(station, fin);
    
    close_train_station(station);
    
    fclose(fin);
}

/**
 * @brief Main function to check all the functions
 * 
 * @return int 0 if everything went alright
 */
int main(void) {

    /* Test all library functions */
    test_arrive_train();
    test_leave_train();
    test_add_train_wagon();
    test_remove_train_wagons();
    test_move_train_wagons();
    test_find_express_train();
    test_find_overload_train();
    test_find_optimal_train();
    test_find_heaviest_sequence_train();
    test_order_train();
    test_fix_overload_train();

    /* Everything went good */
    return 0;
}
