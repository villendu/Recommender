/*-
* Copyright (c) 2012 Hamrouni Ghassen.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

#ifndef TRAINING_SET_H
#define TRAINING_SET_H

#include "model_parameters.h"

//A known user rating
struct rating
{
	double value;
	int user_index;
	int item_index;
	int is_known;
};

typedef struct rating rating_t;

struct training_set
{
    rating_t*        ratings;            //Known ratings
    unsigned int     training_set_size;  //The number of known ratings
    unsigned int     dimensionality;     //dimensionality of the joint latent factor space
    unsigned int     current_rating_index;

    rating_t**       ratings_matrix;
    double**         implicit_feedback;

    double           ratings_sum;
};

typedef struct training_set training_set_t;

/************************************************************************/
/*                          Helper functions                            */
/************************************************************************/

/*
 * init_training_set:  allocate space for the training set
 *                               
 *
 * Arguments:
 *      params        Parameters of the model
 *
 * Returns:
 *      Return an initialized training set.
 *
 */
struct training_set* 
init_training_set(model_parameters_t params);

/*
 * free_training_set:  delete the training set from memory
 */
void
free_training_set(training_set_t* tset);

/*
 * set_known_rating: fill the training set with a known user/item rating
 *                               
 *
 * Arguments:
 *      user_index: The index of a user
 *      user_index: The index of an item
 *      value:      The rating of an item
 *      tset:       The training set to be filled
 *
 */
void 
set_known_rating(int user_index, int item_index, double value, training_set_t* tset);

/*
 * set_known_rating: fill the training set with a known user/item rating
 *                               
 *
 * Arguments:
 *      user_index: The index of a user
 *      user_index: The index of an item
 *      value:      The rating of an item
 *      tset:       The training set to be filled
 *
 */
void
set_implicit_feedback(int user_index, int item_index, training_set_t* tset);

/*
 * user_ratings_average: get the average of the vector formed by 
 *                              the ratings of a user
 *                               
 *
 * Arguments:
 *      user_index: The index of a user
 *      tset:       The training set to be filled
 *      params      Parameters of the model
 *
 */
double 
user_ratings_average(int user_index, training_set_t* tset, model_parameters_t params);

/*
 * item_ratings_average: get the average of the vector formed by 
 *                              the ratings of an item
 *                               
 *
 * Arguments:
 *      item_index: The index of an item
 *      tset:       The training set to be filled
 *      params      Parameters of the model
 *
 */
double 
item_ratings_average(int item_index, training_set_t* tset, model_parameters_t params);

/*
 * implicit_feedback_magnitude: get the magnitude of the vector formed by 
 *                              the implicit preferences of a user
 *                               
 *
 * Arguments:
 *      user_index: The index of a user
 *      tset:       The training set to be filled
 *      params      Parameters of the model
 *
 */
double 
implicit_feedback_magnitude(int user_index, training_set_t* tset, model_parameters_t params);

/*
 * implicit_feedback_sum: get the sum of the vector formed by 
 *                        the implicit preferences of a user
 *                               
 *
 * Arguments:
 *      user_index: The index of a user
 *      tset:       The training set to be filled
 *      params      Parameters of the model
 *
 */
double
implicit_feedback_sum(int user_index, training_set_t* tset, model_parameters_t params);

#endif //TRAINING_SET_H