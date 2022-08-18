#include "./include/station.h"

train_station_t* open_train_station(int platforms_no) {
    // Check for valid input data
    if (platforms_no <= 0)
        return (NULL);

    // Allocate memory for the station
    train_station_t *station = (train_station_t *)malloc(sizeof(train_station_t));

    // Check if memory was allocated
    if (station) {

        // Update data
        station->platforms_no = platforms_no;

        // Allocate memory for platforms
        station->platforms = (train_t **)malloc(platforms_no * sizeof(train_t *));

        // Check if memory was allocated
        if (station->platforms) {
            for (int i = 0; i < platforms_no; ++i) {
                // Allocate memory for every platform
                station->platforms[i] = (train_t *)malloc(sizeof(train_t));

                // Check if memory was allocated
                if (station->platforms[i]) {
                    // Initialize an empty platform
                    station->platforms[i]->locomotive_power = 0;
                    station->platforms[i]->train_wagons = NULL;
                }
            }
        }
    }

    return station;
}

void close_train_station(train_station_t *station) {
    // Check if station is already NULL
    if (station == NULL) return;

    // Check if platform aren't allocated
    if (station->platforms == NULL) return;

    // Free every platforms if it isn't NULL
    for (int i = 0; i < station->platforms_no; ++i) {
        if (station->platforms[i]) {
            // Remove every train
            train_wagon_t *iter = station->platforms[i]->train_wagons;

            // Iterate through train
            while (iter != NULL) {
                // Update locomotive head
                station->platforms[i]->train_wagons =
                station->platforms[i]->train_wagons->next;
                free(iter);
                iter = station->platforms[i]->train_wagons;
            }

            free(station->platforms[i]);
        }
    }

    // Free platforms if it isn't NULL
    free(station->platforms);

    // Free station
    free(station);
}

void show_existing_trains(train_station_t *station, FILE *f) {
    // Check if data is valid
    if (station == NULL) return;

    // Check if platforms are valid
    if (station->platforms == NULL) return;

    // Check if file is opened for writing
    if (f == NULL) return;

    // Iterate through platforms
    for (int i = 0; i < station->platforms_no; ++i) {
        if (station->platforms[i]) {
            // Print platform index and power of locomotive
            fprintf(f, "%d: ", i);

            // Check if exists a train on platform
            if (station->platforms[i]->train_wagons) {
                fprintf(f, "(%d)", station->platforms[i]->locomotive_power);

                // Point to non-motor locomotives
                train_wagon_t *iter = station->platforms[i]->train_wagons->next;

                // Iterate through locomotive
                while(iter != NULL) {
                    fprintf(f, "-|%d|", iter->weight);
                    iter = iter->next;
                }
            }
            fprintf(f, "\n");
        }
    }
}

void arrive_train(train_station_t *station, int platform, int locomotive_power) {
    // Check for memory
    if (station == NULL) return;

    // A locomotive cannot be negative
    if (locomotive_power < 0) return;

    // Platform number cannot exced the limit
    if (platform >= station->platforms_no || platform < 0) return;

    // Check for memory
    if (station->platforms == NULL) return;

    // Check for memory
    if (station->platforms[platform] == NULL) return;

    // Check if a train is already on the platform
    if (station->platforms[platform]->train_wagons) return;

    // Update data
    station->platforms[platform]->locomotive_power = locomotive_power;

    // Allocate memory for new motor locomotive
    station->platforms[platform]->train_wagons = (train_wagon_t *)malloc(sizeof(train_wagon_t));

    // Check if memory was allocated
    if (station->platforms[platform]->train_wagons) {
        // Initialize the new motor locomotive
        station->platforms[platform]->train_wagons->weight = 0;
        station->platforms[platform]->train_wagons->next = NULL;
    }
}

void leave_train(train_station_t *station, int platform) {
    // Check for memory
    if (station == NULL) return;

    // Platform number cannot exced the limit
    if (platform >= station->platforms_no || platform < 0) return;

    // Check for memory
    if (station->platforms == NULL) return;

    // Check for memory
    if (station->platforms[platform] == NULL) return;

    // Check if train is already gone
    if (station->platforms[platform]->train_wagons == NULL) return;

    train_wagon_t *iter = station->platforms[platform]->train_wagons;

    // Iterate through train
    while (iter != NULL) {
        // Update locomotive head
        station->platforms[platform]->train_wagons = 
        station->platforms[platform]->train_wagons->next;
        free(iter);
        iter = station->platforms[platform]->train_wagons;
    }
}

void add_train_car(train_station_t *station, int platform, int weight) {
    // Check for memory
    if (station == NULL) return;

    // A wagon cannot have negative
    if (weight < 0) return;

    // Platform number cannot exced the limit
    if (platform >= station->platforms_no || platform < 0) return;

    // Check if platforms are allocated
    if (station->platforms == NULL) return;

    // Check if platform is allocated
    if (station->platforms[platform] == NULL) return;

    // Check if a train is on platform
    if (station->platforms[platform]->train_wagons == NULL) return;

    train_wagon_t *iter = station->platforms[platform]->train_wagons;

    // Iterate until hit last wagon
    while (iter->next != NULL)
        iter = iter->next;

    // Allocate a new wagon
    train_wagon_t *newCell = (train_wagon_t *)malloc(sizeof(train_wagon_t));

    // Check for memory allocation
    if (newCell) {
        // Update newCell data
        newCell->weight = weight;
        newCell->next = NULL;

        // Update the train
        iter->next = newCell;
    }
}

void remove_train_cars(train_station_t *station, int platform, int weight) {
    // Check for memory
    if (station == NULL) return;

    // A wagon cannot have negative
    if (weight < 0) return;

    // Platform number cannot exced the limit
    if (platform >= station->platforms_no || platform < 0) return;

    // Check if platforms are allocated
    if (station->platforms == NULL) return;

    // Check if platform is allocated
    if (station->platforms[platform] == NULL) return;

    // Check if a train is on platform
    if (station->platforms[platform]->train_wagons == NULL) return;

    // We need previous wagon and current wagon
    // So we could delete a wagon
    train_wagon_t *prev_locm = station->platforms[platform]->train_wagons;
    train_wagon_t *curr_locm = station->platforms[platform]->train_wagons->next;

    // Iterate until hit end of the train
    while (curr_locm != NULL) {
        // Check the wagon's weight
        if (curr_locm->weight == weight) {
            // Update links
            prev_locm->next = curr_locm->next;

            // Free memory
            free(curr_locm);
            curr_locm = NULL;
        }

        // If curr == NULL it was deleted
        // So curr gets new node while prev stays
        // else both of them go on the next wagon
        if (curr_locm) {
            prev_locm = curr_locm;
            curr_locm = curr_locm->next;
        } 
        else {
            curr_locm = prev_locm->next;
        }
    }
}

void move_train_cars(train_station_t *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
    // Check if station is allocated
    if (station == NULL) return;

    // Platform numbers cannot exced limit
    if (platform_a >= station->platforms_no || platform_a < 0) return;
    if (platform_b >= station->platforms_no || platform_b < 0) return;

    // Cannot insert or extract wagon on a invalid position
    if (pos_a < 1 || pos_b < 1 || cars_no <= 0) return;

    // Check for every platform if exists trains
    if (station->platforms == NULL) return;
    if (station->platforms[platform_a] == NULL) return;
    if (station->platforms[platform_b] == NULL) return;
    if (station->platforms[platform_a]->train_wagons == NULL) return;
    if (station->platforms[platform_b]->train_wagons == NULL) return;

    // Set iterators through both platforms
    train_wagon_t *iter_a = station->platforms[platform_a]->train_wagons;
    train_wagon_t *iter_b = station->platforms[platform_b]->train_wagons;
    
    // Find length of the train (including locomotive)
    int length_a = 0, length_b = 0;

    while (iter_a) {
        iter_a = iter_a->next;
        ++length_a;
    }

    while (iter_b) {
        iter_b = iter_b->next;
        ++length_b;
    }

    // Check if pos_a is a valid position
    if (pos_a > length_a) return;

    // Check if we can remove cars_no wagons
    if (pos_a + cars_no > length_a) return;

    // Check if insertion position is valid
    if (pos_b > length_b) return;

    // Set first train new iterators
    train_wagon_t *prev_iter_a = station->platforms[platform_a]->train_wagons;
    iter_a = station->platforms[platform_a]->train_wagons->next;

    // Set iterator to pos_a wagon
    while (--pos_a) {
        prev_iter_a = iter_a;
        iter_a = iter_a->next;
    }

    // Set second train new iterators
    iter_b = station->platforms[platform_b]->train_wagons;
    
    // Set iterator to pos_b - 1 wagon
    while (--pos_b) {
        iter_b = iter_b->next;
    }

    // Insert wagons in train No2
    for (int i = 0; i < cars_no; ++i) {
        // Update links
        prev_iter_a->next = iter_a->next;
        iter_a->next = iter_b->next;
        iter_b->next = iter_a;
        
        // Move to the next wagon 
        iter_b = iter_a;
        iter_a = prev_iter_a->next;
    }
}

int calculate_power_weight(train_t *platform, char lim) {
    if (lim) {
        // Check if platforms exists
        if (platform == NULL) return INT_MAX;

        // Check if trains exists
        if (platform->train_wagons == NULL) return INT_MAX;
    }

    // Check if platforms exists
    if (platform == NULL) return INT_MIN;

    // Check if trains exists
    if (platform->train_wagons == NULL) return INT_MIN;

    int pow_weight = platform->locomotive_power;

    train_wagon_t *iter = platform->train_wagons->next;

    // Calculate the power of platform
    while (iter) {
        pow_weight -= iter->weight;
        iter = iter->next;
    }

    return pow_weight;
}

int find_express_train(train_station_t *station) {
    // Check for memory
    if (station == NULL) return -1;

    // Check if platforms are allocated
    if (station->platforms == NULL) return -1;
    
    // Get power of first platforms if exists
    int index_exp_tr = 0;
    int max_pow_weight = calculate_power_weight(station->platforms[0], 0);

    for (int i = 1; i < station->platforms_no; ++i) {
        // Calculate power of every station
        int new_max = calculate_power_weight(station->platforms[i], 0);

        // Update the express train
        if (new_max > max_pow_weight) {
            max_pow_weight = new_max;
            index_exp_tr = i;
        }
    }

    // Return index of the fastest train
    return index_exp_tr;
}

int find_overload_train(train_station_t *station) {
    // Check for memory
    if (station == NULL) return -1;

    // Check if platforms are allocated
    if (station->platforms == NULL) return -1;

    // Iterate through every platforms
    for (int i = 0; i < station->platforms_no; ++i) {
        // Calculate power of the platform
        if (calculate_power_weight(station->platforms[i], 1) < 0) {
            // If power is negative we found the train 
            return i;
        }
    }

    // No train was found
    return -1;
}

int find_optimal_train(train_station_t *station) {
    // Check for memory
    if (station == NULL) return -1;

    // Check if platforms are allocated
    if (station->platforms == NULL) return -1;
    
    // Get power of first platforms if exists
    int index_exp_tr = 0;
    int min_pow_weight = calculate_power_weight(station->platforms[0], 1);

    for (int i = 1; i < station->platforms_no; ++i) {
        // Calculate power of every station
        int new_min = calculate_power_weight(station->platforms[i], 1);

        // Update the optimal train
        if (new_min > 0 && new_min < min_pow_weight) {
            min_pow_weight = new_min;
            index_exp_tr = i;
        }
    }

    // Return index of the optimal train
    return index_exp_tr;
}

int find_heaviest_sequence_train(train_station_t *station, int cars_no, train_wagon_t **start_car) {
    *start_car = NULL;

    // Check if number of wag is valid
    if (cars_no <= 0) return -1;

    // Check for memory
    if (station == NULL) return -1;

    // Check if platforms are allocated
    if (station->platforms == NULL) return -1;

    int over_weight_final = 0, heavy_train = -1;

    // Iterate through every platform
    for (int i = 0; i < station->platforms_no; ++i) {
        // Check if platform is allocated
        if (station->platforms[i]) {
            int over_weight = 0;

            train_wagon_t *over_wag = NULL;
            train_wagon_t *prev = station->platforms[i]->train_wagons;
            train_wagon_t *iter = prev;

            // Iterate through every sequence of wagons
            while (iter) {
                iter = prev->next;
                prev = iter;
                int seq_weight = 0, it;

                // Calculate weight of a sequence
                for (it = 0; it < cars_no && iter != NULL; ++it, iter = iter->next) {
                    seq_weight += iter->weight;
                }

                // If it != cars_no, it means
                // There are not enough wagons
                if (it != cars_no) break;
                
                // Interchange the biggest wagon
                if (seq_weight > over_weight) {
                    over_weight = seq_weight;
                    over_wag = prev;
                }
            }

            // Interchange the biggest wagon from
            // All platforms
            if (over_weight > over_weight_final) {
                over_weight_final = over_weight;
                *start_car = over_wag;

                // Update platform
                heavy_train = i;
            } 
        }
    }

    return heavy_train;
}

void swap_wagon(train_wagon_t *prevNode, train_wagon_t *currentNode, train_wagon_t *nextNode) {
    prevNode->next = nextNode;
    currentNode->next = nextNode->next;
    nextNode->next = currentNode;
}

void order_train(train_station_t *station, int platform) {
    // Check for memory
    if (station == NULL) return;

    // Check if platforms are allocated
    if (station->platforms == NULL) return;

    // Check if platform is allocated
    if (station->platforms[platform] == NULL) return;

    // Check if train is still on the platform
    if (station->platforms[platform]->train_wagons == NULL) return;

    // Point to the first wagon
    train_wagon_t *iter_curr = station->platforms[platform]->train_wagons->next;
    
    // Nothing to do, return
    if (iter_curr == NULL) return;

    // Length of the train
    int train_length = 0;
    
    // Find length of the train
    while(iter_curr) {
        ++train_length;
        iter_curr = iter_curr->next;
    }

    // Bubble sort method
    for (int i = 0; i < train_length; ++i) {
        // Checks if was done a single swap
        int not_swapped_at_all = 1;

        // Point to locomotive and first wagon
        train_wagon_t *iter_prev = station->platforms[platform]->train_wagons;
        iter_curr = iter_prev->next;

        // Iterate through wagons
        for(int j = 0; j < train_length - i - 1; ++j) {
            // Checks if there was a swap between two wagons
            int not_swapped = 1;

            // Swap wagons in descending order
            if (iter_curr->weight < iter_curr->next->weight) {
                // Function to swap wagon
                swap_wagon(iter_prev, iter_curr, iter_curr->next);

                // There was a swap so change values to zero
                not_swapped = 0;
                not_swapped_at_all = 0;

                // Update previous
                // iter_curr is already in the right place
                iter_prev = iter_prev->next;
            }

            // If no swap happened go to next wagon
            if (not_swapped) {
                iter_prev = iter_curr;
                iter_curr = iter_curr->next;
            }
        }

        // No swap means list is sorted
        if (not_swapped_at_all) return;
    }
}

void fix_overload_train(train_station_t *station) {
    // Find overloaded train
    int over_train = find_overload_train(station);

    // No train is overloaded
    if (over_train == -1) return;

    int min_power_index = 0, min_power_value = __INT_MAX__;

    // Point to overloaded train
    train_wagon_t *iter = station->platforms[over_train]->train_wagons;

    // Find index of optimal value to remove
    for (int i = 0; iter != NULL; ++i, iter = iter->next) {
        // Calculate the power of a train if remove iter-wagon
        int relative_power = calculate_power_weight(station->platforms[over_train], 0)
                             + iter->weight;

        // If train has a positive power without
        // iter-wagon and iter-wagon makes 
        // train to be optimal update new index
        if (relative_power >= 0 && relative_power < min_power_value) {
            min_power_value = relative_power;
            min_power_index = i;
        }
    }

    
    iter = station->platforms[over_train]->train_wagons;
    train_wagon_t *prev = NULL;

    // Iterate to optimal wagon to remove
    while (min_power_index--) {
        prev = iter;
        iter = iter->next;
    }

    // Remove optimal wagon to remove
    // And update links
    prev->next = iter->next;
    free(iter);
}
