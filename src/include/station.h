#ifndef _STATION_H_
#define _STATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/**
 * @brief Definition of a train car object
 * 
 */
typedef struct train_wagon_s {
    int weight;                             /* Weight of the train wagon */
    struct train_wagon_s *next;             /* Pointer to the next wagon */
} train_wagon_t;

/**
 * @brief Definition of a train object
 * 
 */
typedef struct train_s {
    int locomotive_power;                   /* The power of the locomotive */
    train_wagon_t *train_wagons;            /* Pointer to the first wagon */
} train_t;

/**
 * @brief Definition of a train station object
 * 
 */
typedef struct train_station_s {
    int platforms_no;                       /* The number of station platforms */
    train_t **platforms;                    /* Array of platforms allocated for train arival */
} train_station_t;


train_station_t*        open_train_station                  (int32_t platforms_no);
void                    close_train_station                 (train_station_t *station);
void                    show_existing_trains                (train_station_t *station, FILE *fin);

void                    arrive_train                        (train_station_t *station, int32_t platform, int32_t locomotive_power);
void                    leave_train                         (train_station_t *station, int32_t platform);
void                    add_train_car                       (train_station_t *station, int32_t platform, int32_t car_weight);
void                    remove_train_cars                   (train_station_t *station, int32_t platform, int32_t car_weight);
void                    move_train_cars                     (train_station_t *station, int32_t platform_f, int32_t pos_f, int32_t cars_no, int32_t platform_s, int32_t pos_s);

int32_t                 find_express_train                  (train_station_t *station);
int32_t                 find_overload_train                 (train_station_t *station);
int32_t                 find_optimal_train                  (train_station_t *station);
int32_t                 find_heaviest_sequence_train        (train_station_t *station, int32_t cars_no, train_wagon_t **start_car);

void                    order_train                         (train_station_t *station, int32_t platform);
void                    fix_overload_train                  (train_station_t *station);

#endif /* _STATION_H_ */
