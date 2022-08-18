#include "./include/station.h"

/**
 * @brief Function to allocate a station object on the ram memory.
 * The function will also open the data base for the train station
 * 
 * @param platforms_no numbers of the platforms that the station currenty has.
 * @return train_station_t* a pointer to an allocated station object or NULL if function failed
 */
train_station_t* open_train_station(int32_t platforms_no) {
    /* Check if the input data is valid */
    if (platforms_no <= 0) {
        return NULL;
    }

    /* Allocate memory for the train station object */
    train_station_t *station = malloc(sizeof(*station));

    /* Check if staion was allocated successfully */
    if (station != NULL) {

        /* Set the station platforms number */
        station->platforms_no = platforms_no;

        /* Allocate the platforms for the station */
        station->platforms = malloc(sizeof(*station->platforms) * platforms_no);

        /* Check if platforms were allocated successfully */
        if (station->platforms != NULL) {
            for (int32_t iter = 0; iter < platforms_no; ++iter) {
                
                /* Allocate a non existent train */
                station->platforms[iter] = malloc(sizeof(*station->platforms[iter]));

                /* Check if train was allocated */
                if (station->platforms[iter] != NULL) {
                    station->platforms[iter]->locomotive_power = 0;
                    station->platforms[iter]->train_wagons = NULL;
                }
            }
        }
    }

    /* Return a pointer to an allocated station object or NULL */
    return station;
}

/**
 * @brief Function to free the loaded memory for a station.
 * 
 * @param station a pointer to an allocated station object
 */
void close_train_station(train_station_t *station) {
    /* Check if the station can be closed */
    if ((station == NULL) || (station->platforms == NULL)) {
        return;
    }

    /* Close the station */
    for (int32_t iter = 0; iter < station->platforms_no; ++iter) {
        
        /* Close one station platform */
        if (station->platforms[iter] != NULL) {
            train_wagon_t *wagon = station->platforms[iter]->train_wagons;

            /* Free memory loaded for wagons */
            while (wagon != NULL) {
                station->platforms[iter]->train_wagons = station->platforms[iter]->train_wagons->next;
                
                free(wagon);
                
                wagon = station->platforms[iter]->train_wagons;
            }

            /* Free memory loaded for platform */
            free(station->platforms[iter]);
            station->platforms[iter] = NULL;
        }
    }

    /* Free memory loaded for platforms */
    free(station->platforms);
    station->platforms = NULL;

    /* Free memory for station */
    free(station);
}

/**
 * @brief Function to printf in the "fin" stream
 * the station with all alocated trains and wagons
 * (if there exists a train on a desired platform)
 * 
 * @param station a pointer to an allocated station object
 * @param fin a pointer to an allocated file object
 */
void show_existing_trains(train_station_t *station, FILE *fin) {
    /* Check if input data is valid */
    if ((station == NULL) || (station->platforms == NULL) || (fin == NULL)) {
        return;
    }

    /* Print every platform */
    for (int32_t iter = 0; iter < station->platforms_no; ++iter) {
        
        /* Check if the platform is allocated an can be printed */
        if (station->platforms[iter] != NULL) {
            
            /* Print the platform number */
            fprintf(fin, "%d: ", iter);

            /* Check if exists a train on the platform */
            if (station->platforms[iter]->train_wagons != NULL) {
                fprintf(fin, "(%d)", station->platforms[iter]->locomotive_power);

                train_wagon_t *wagon = station->platforms[iter]->train_wagons->next;

                /* Print the wagons weight */
                while(wagon != NULL) {
                    fprintf(fin, "-|%d|", wagon->weight);

                    wagon = wagon->next;
                }
            }

            fprintf(fin, "\n");
        }
    }
}

/**
 * @brief Function to allocate an arriving train on a platform in the loaded station.
 * 
 * @param station a pointer to an allocated station object
 * @param platform the platform number to put the train
 * @param locomotive_power the power of the arriving train
 */
void arrive_train(train_station_t *station, int32_t platform, int32_t locomotive_power) {
    /* Check if the platform and locomotive power are valid */
    if ((locomotive_power < 0) || (platform >= station->platforms_no) || (platform < 0)) {
        return;
    }

    /* Check if station is allocated and can allocate a train */
    if ((station == NULL) || (station->platforms == NULL) || (station->platforms[platform] == NULL)) {
        return;
    }

    /* Check if on desired station already exists a train */
    if (station->platforms[platform]->train_wagons != NULL) {
        return;
    }

    /* Set locomotive power */
    station->platforms[platform]->locomotive_power = locomotive_power;

    /* Allocate the locomotive wagon car */
    station->platforms[platform]->train_wagons = malloc(sizeof(*station->platforms[platform]->train_wagons));

    /* Check if locomotive was allocated */
    if (station->platforms[platform]->train_wagons != NULL) {

        /* Set default values for an arrived train */
        station->platforms[platform]->train_wagons->weight = 0;
        station->platforms[platform]->train_wagons->next = NULL;
    }
}

/**
 * @brief Function to free a platform from a train (the train leaves).
 * 
 * @param station a pointer to an allocated station object
 * @param platform the number of the platform to free from train object
 */
void leave_train(train_station_t *station, int32_t platform) {
    /* Check if the desired platform exists in the loaded station */
    if ((platform >= station->platforms_no) || (platform < 0)) {
        return;
    }

    /* Check if station object is allocated */
    if ((station == NULL) || (station->platforms == NULL)) {
        return;
    }

    /* Check if the platform is allocated and can be freed from a train object */
    if ((station->platforms[platform] == NULL) || (station->platforms[platform]->train_wagons == NULL)) {
        return;
    }

    /* Point to the first wagon */
    train_wagon_t *wagon = station->platforms[platform]->train_wagons;

    /* Free all wagons */
    while (wagon != NULL) {
        station->platforms[platform]->train_wagons = station->platforms[platform]->train_wagons->next;
        
        free(wagon);
        
        wagon = station->platforms[platform]->train_wagons;
    }
}

/**
 * @brief Function to add a wagon to a train from a specified platform
 * 
 * @param station a pointer to an allocated station onject
 * @param platform the number of the platform to add a new wagon
 * @param wag_weight the weight of the new added wagon
 */
void add_train_wagon(train_station_t *station, int32_t platform, int32_t wag_weight) {
    /* Check if the wagon can be inserted into the train */
    if ((wag_weight < 0) || (platform >= station->platforms_no) || (platform < 0)) {
        return;
    }

    /* Check if the station object is allocated */
    if ((station == NULL) || (station->platforms == NULL) || (station->platforms[platform] == NULL)) {
        return;
    }

    /* Check if there exists a train to add a new wagon */
    if (station->platforms[platform]->train_wagons == NULL) {
        return;
    }

    train_wagon_t *wagon = station->platforms[platform]->train_wagons;

    /* Iterate to the last wagon */
    while (wagon->next != NULL) {
        wagon = wagon->next;
    }

    /* Create a new wagon */
    train_wagon_t *new_wagon = malloc(sizeof(*new_wagon));

    /* Check if wagon waas created successfully */
    if (new_wagon != NULL) {
        new_wagon->weight = wag_weight;
        new_wagon->next = NULL;

        wagon->next = new_wagon;
    }
}

/**
 * @brief Function to remove all the wagons from the specified platforms
 * that have the same weight as the input weight. Function will fail
 * if no train exists on the platform
 * 
 * @param station a pointer to an allocated station object
 * @param platform the number of the platform to remove wagons
 * @param wag_weight the desired weight to remove trains
 */
void remove_train_wagons(train_station_t *station, int32_t platform, int32_t wag_weight) {
    /* Check if the input data is valid to remove wagons */
    if ((wag_weight < 0) || (platform >= station->platforms_no) || (platform < 0)) {
        return;
    }

    /* Check if station object is allocated */
    if ((station == NULL) || (station->platforms == NULL) || (station->platforms[platform] == NULL)) {
        return;
    }

    /* Check if there exists a train on the platform */
    if (station->platforms[platform]->train_wagons == NULL) {
        return;
    }

    train_wagon_t *prev_wagon = station->platforms[platform]->train_wagons;
    train_wagon_t *wagon = prev_wagon->next;

    /* Remove all desired wagons */
    while (wagon != NULL) {

        /* One wagon was found */
        if (wagon->weight == wag_weight) {
            prev_wagon->next = wagon->next;

            free(wagon);
            wagon = NULL;
        }

        /* Update next pointers */
        if (wagon != NULL) {
            prev_wagon = wagon;
            wagon = wagon->next;
        } else {
            wagon = prev_wagon->next;
        }
    }
}

/**
 * @brief Function to move "wagons_no" wagons from the train from "platform_f" starting after
 * "pos_f" wagon and add them to the train from "platfor_s" after the "pos_s" wagon
 * 
 * @param station a pointer to an allocated station object
 * @param platform_f platform of the first train to remove wagons
 * @param pos_f starting wagon to remove wagons
 * @param wagons_no number of wagons to remove from first train
 * @param platform_s platform of the second train to add wagons
 * @param pos_s starting wagon to add wagons
 */
void move_train_wagons(train_station_t *station, int32_t platform_f, int32_t pos_f, int32_t wagons_no, int32_t platform_s, int32_t pos_s) {
    /* Check if platform numbers are valid for the loaded station */
    if ((platform_f >= station->platforms_no) || (platform_f < 0) || (platform_s >= station->platforms_no) || (platform_s < 0)) {
        return;
    }

    /* Check if any wagons should be removed adn added */
    if ((pos_f < 1) || (pos_s < 1) || (wagons_no <= 0)) {
        return;
    }

    /* Check if the staton object is allocated */
    if ((station == NULL) || (station->platforms == NULL) || (station->platforms[platform_f] == NULL) || (station->platforms[platform_s] == NULL)) {
        return;
    }

    /* Check if there exists trains to remove/add wagons */
    if ((station->platforms[platform_f]->train_wagons == NULL) || (station->platforms[platform_s]->train_wagons == NULL)) {
        return;
    }

    train_wagon_t *wagon_f = station->platforms[platform_f]->train_wagons;
    train_wagon_t *wagon_s = station->platforms[platform_s]->train_wagons;
    
    int32_t len_f = 0, len_s = 0;

    /* Count first train wagons */
    while (wagon_f != NULL) {
        wagon_f = wagon_f->next;
        
        ++len_f;
    }

    /* Count second train wagons */
    while (wagon_s != NULL) {
        wagon_s = wagon_s->next;
        
        ++len_s;
    }

    /* Check if the operation can be performed */
    if ((pos_f > len_f) || (pos_f + wagons_no > len_f) || (pos_s > len_s)) {
        return;
    }

    train_wagon_t *prev_wagon_f = station->platforms[platform_f]->train_wagons;
    wagon_f = prev_wagon_f->next;

    /* Go to the first wagon to move */
    while (--pos_f > 0) {
        prev_wagon_f = wagon_f;
        wagon_f = wagon_f->next;
    }

    wagon_s = station->platforms[platform_s]->train_wagons;
    
    /* Go to the first wagon to add */
    while (--pos_s > 0) {
        wagon_s = wagon_s->next;
    }

    for (int32_t iter = 0; iter < wagons_no; ++iter) {
        
        /* Move the wagon and update links */
        prev_wagon_f->next = wagon_f->next;
        wagon_f->next = wagon_s->next;
        wagon_s->next = wagon_f;
        
        /* Add the wagon and update links*/
        wagon_s = wagon_f;
        wagon_f = prev_wagon_f->next;
    }
}

/**
 * @brief Function to calculate the power of a train. The result
 * may deppend according to slect variable
 * 
 * @param train a pointer to an allocated train to find the power
 * @param select selection variable
 * @return int32_t INT_MAX/INT_MIN or the power of the train
 */
int32_t calculate_power_weight(train_t *train, uint8_t select) {
    /* Check if the train power can be calculated */
    if ((select != 0) && ((train == NULL) || (train->train_wagons == NULL))) {
        return INT_MAX;
    }

    /* Check if the train power can be calculated */
    if ((train == NULL) || (train->train_wagons == NULL)) {
        return INT_MIN;
    }

    int32_t pow_weight = train->locomotive_power;

    train_wagon_t *wagon = train->train_wagons->next;

    /* Calculate the train power */
    while (wagon != NULL) {
        pow_weight -= wagon->weight;

        wagon = wagon->next;
    }

    /* Return the train power */
    return pow_weight;
}

/**
 * @brief Function to find the express train.
 * An express train is the train that has the biggest power.
 * 
 * @param station a pointer to an allocated station object
 * @return int32_t the number of the platform where the train stays
 */
int32_t find_express_train(train_station_t *station) {
    /* Check if the station is allocated */
    if ((station == NULL) || (station->platforms == NULL)) {
        return -1;
    }

    /* Initialize the express train index */
    int32_t idx_express = 0;
    int32_t max_pow_weight = calculate_power_weight(station->platforms[0], 0);

    /* Find the express train */
    for (int32_t iter = 1; iter < station->platforms_no; ++iter) {
        int32_t new_max = calculate_power_weight(station->platforms[iter], 0);

        /* Update the new express train */
        if (new_max > max_pow_weight) {
            max_pow_weight = new_max;
            idx_express = iter;
        }
    }

    /* Return the platform number of the express train */
    return idx_express;
}

/**
 * @brief Find the first occurence of a train that is overloaded.
 * A train is overloaded if its power is negative.
 * 
 * @param station a pointer to an allocated station object
 * @return int32_t the number of the platform where the train stays
 */
int32_t find_overload_train(train_station_t *station) {
    /* Check if the station is loaded */
    if ((station == NULL) || (station->platforms == NULL)) {
        return -1;
    }

    /* Find the first occurence of the overloaded train */
    for (int32_t iter = 0; iter < station->platforms_no; ++iter) {
        if (calculate_power_weight(station->platforms[iter], 1) < 0) {
            return iter;
        }
    }

    /* No overloaded train was found */
    return -1;
}

/**
 * @brief Function to find the optimal train.
 * An optimal train is the train that the difference between
 * its locomotive power adn the sum of the wagons weight is minimal.
 * 
 * @param station a pointer to an allocated station object
 * @return int32_t the number of the platform where the train stays
 */
int32_t find_optimal_train(train_station_t *station) {
    /* Check if station is loaded */
    if ((station == NULL) || (station->platforms == NULL)) {
        return -1;
    }
    
    /* Initialize optimal train index */
    int32_t idx_optimal = 0;
    int32_t min_pow_weight = calculate_power_weight(station->platforms[0], 1);

    /* Find the optimal train */
    for (int32_t iter = 1; iter < station->platforms_no; ++iter) {
        int32_t new_min = calculate_power_weight(station->platforms[iter], 1);

        /* Update the new optimal train */
        if ((new_min > 0) && (new_min < min_pow_weight)) {
            min_pow_weight = new_min;
            idx_optimal = iter;
        }
    }

    /* Return the platform number of the optimal train */
    return idx_optimal;
}

/**
 * @brief Function to find the train with the biggest weight for
 * a continuous sequence of wagons of length "wagons_no". Function
 * will return the platform of the found train and in start_wagon
 * will put the first wagon that makes the biggest weight sequence
 * form the station
 * 
 * @param station[in] a pointer to an allocated station object
 * @param wagons_no[in] the length of the specified sequence
 * @param start_wagon[out] a pointer to the first sequence wagon
 * @return int32_t the number of the platform where the train stays
 */
int32_t find_heaviest_sequence_train(train_station_t *station, int32_t wagons_no, train_wagon_t **start_wagon) {
    /* Set the default value for start wagon */
    *start_wagon = NULL;

    /* Check if desirder sequence can be calculated */
    if ((wagons_no <= 0) || (station == NULL) || (station->platforms == NULL)) {
        return -1;
    }

    int32_t over_weight_final = 0, heaviest_train = -1;

    /* Find the train with the heaviest sequence */
    for (int32_t iter_i = 0; iter_i < station->platforms_no; ++iter_i) {
        
        /* Check if there exists a train on the platform */
        if (station->platforms[iter_i] != NULL) {
            int32_t over_weight = 0;

            train_wagon_t *over_wagon = NULL;
            train_wagon_t *prev_wagon = station->platforms[iter_i]->train_wagons;
            train_wagon_t *wagon = prev_wagon;

            /* Traverse all the sequences */
            while (wagon != NULL) {
                wagon = prev_wagon->next;
                prev_wagon = wagon;

                int32_t seq_weight = 0, iter_j;

                /* Calculate the weight of the sequence */
                for (iter_j = 0; iter_j < wagons_no && wagon != NULL; ++iter_j, wagon = wagon->next) {
                    seq_weight += wagon->weight;
                }

                /* No more sequences can be calculated */
                if (iter_j != wagons_no) {
                    break;
                }
                
                /* Update the new local heaviest sequence */
                if (seq_weight > over_weight) {
                    over_weight = seq_weight;
                    over_wagon = prev_wagon;
                }
            }

            /* Update the global heaviest sequence */
            if (over_weight > over_weight_final) {
                over_weight_final = over_weight;
                *start_wagon = over_wagon;

                heaviest_train = iter_i;
            } 
        }
    }

    /* Return the platform number of the train with heaviest sequence */
    return heaviest_train;
}

/**
 * @brief Function to swap two wagons
 * 
 * @param prev_wagon a pointer to the previous wagon
 * @param wagon a pointer to the first wagons to swap
 * @param next_wagon a pointer to the second wagon to swap
 */
void swap_wagons(train_wagon_t *prev_wagon, train_wagon_t *wagon, train_wagon_t *next_wagon) {
    if ((prev_wagon != NULL) || (wagon != NULL) || (next_wagon != NULL)) {
        prev_wagon->next = next_wagon;
        wagon->next = next_wagon->next;
        next_wagon->next = wagon; 
    }
}

/**
 * @brief Function to order the train wagons by their weights.
 * The sorting will be from bigger to smaller.
 * 
 * @param station a pointer to an allocated station object
 * @param platform the number of the platform that train stays
 */
void order_train(train_station_t *station, int32_t platform) {
    /* Check if the train can be sorted */
    if ((station == NULL) || (station->platforms == NULL) || (station->platforms[platform] == NULL)) {
        return;
    }

    /* Check if exists a train on the platform */
    if (station->platforms[platform]->train_wagons == NULL) {
        return;
    }

    train_wagon_t *wagon = station->platforms[platform]->train_wagons->next;
    
    /* Check if there are wagons to sort */
    if (wagon == NULL) return;

    int32_t train_length = 0;
    
    /* Find the numbers of wagons */
    while(wagon != NULL) {
        wagon = wagon->next;

        ++train_length;
    }

    /* Sort the train */
    for (int32_t iter_i = 0; iter_i < train_length; ++iter_i) {
        uint8_t not_swapped_at_all = 1;

        train_wagon_t *prev_wagon = station->platforms[platform]->train_wagons;
        wagon = prev_wagon->next;

        /* Swap wagons */
        for(int32_t iter_j = 0; iter_j < train_length - iter_i - 1; ++iter_j) {
            int32_t not_swapped = 1;

            if (wagon->weight < wagon->next->weight) {
                swap_wagons(prev_wagon, wagon, wagon->next);

                not_swapped = 0;
                not_swapped_at_all = 0;

                prev_wagon = prev_wagon->next;
            }

            if (not_swapped == 1) {
                prev_wagon = wagon;
                wagon = wagon->next;
            }
        }

        /* The train is sorted */
        if (not_swapped_at_all == 1) {
            return;
        }
    }
}

/**
 * @brief Function to fix an overloaded train.
 * The function will remove just one wagon such that
 * the train will become an optimal train.
 * 
 * @param station a pointer to an allocated station object
 */
void fix_overload_train(train_station_t *station) {
    /* Find the first overloaded train from the station */
    int32_t idx_overload = find_overload_train(station);

    /* No overloaded train was found */
    if (idx_overload == -1) {
        return;
    }

    /* Initialize the remove wagon index */
    int32_t min_pow_idx = 0, min_pow_value = INT_MAX;

    train_wagon_t *wagon = station->platforms[idx_overload]->train_wagons;

    /* Find the wagon to remove */
    for (int32_t iter = 0; wagon != NULL; ++iter, wagon = wagon->next) {
        int32_t relative_pow = calculate_power_weight(station->platforms[idx_overload], 0) + wagon->weight;

        if ((relative_pow >= 0) && (relative_pow < min_pow_value)) {
            min_pow_value = relative_pow;
            min_pow_idx = iter;
        }
    }
    
    train_wagon_t *prev_wagon = NULL;
    wagon = station->platforms[idx_overload]->train_wagons;

    /* Iterate to the wagon to remove it */
    while (min_pow_idx--) {
        prev_wagon = wagon;
        wagon = wagon->next;
    }

    /* Remove the wagon and update links */
    prev_wagon->next = wagon->next;

    free(wagon);
    wagon = NULL;
}
