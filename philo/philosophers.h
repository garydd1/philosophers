/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:53:12 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 19:47:20 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# define MAX_EAT -42
# define FORK "Has taken a fork."
# define EAT  "Is eating."
# define THINK "Is thinking..."
# define SLEEP "Is sleeping."
# define WOKE "Woke up with hunger!"
# define RIP "*****************RIP*******************"
# define RAP "*****************RAP*******************"
# define WT   "\x1b[1;37m"
# define YW "\x1b[1;33m"
# define RED "\x1b[1;31m"
# define BLUE "\x1b[1;36m"
# define PINK "\x1b[1;35m"
# define RST    "\x1b[0m"

typedef struct s_philosopher	t_philo;
typedef struct timeval			t_time;

typedef enum e_atributes
{
	TTDIE,
	TTEAT,
	TTSLEEP,
	MUST_EAT,
	ATR_COUNT
}	t_atributes;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_flags
{
	bool	must_eat;
}	t_flags;

typedef struct s_macro_data
{
	int				philo_nbr;
	int				argc;
	char			**argv;
	int				atributes[ATR_COUNT];
	int				i;
	long long		born_time;
	bool			end;
	bool			stop;
	pthread_mutex_t	genesis;
	pthread_mutex_t	stdout_mtx;
	pthread_mutex_t	aux_mtx;
	t_time			the_time;
	t_fork			*forks;
	t_philo			*philos;
}	t_data;

typedef struct s_philosopher
{
	bool			alive;
	bool			allowed_to_eat;
	int				id;
	int				atributes[ATR_COUNT];
	int				eat_count;
	long long		born_time;
	long long		last_ate;
	int				frst_fork;
	int				scnd_fork;
	pthread_t		tid;
	t_time			eat_time;
	t_data			*data;	
}	t_philo;

//MAIN

void			*physis(void *arg);
bool			stop_check(t_data *data);

//INIT

int				init(t_data *data, int argc, char **argv);
void			unpick_forks(t_philo *philo, t_data *data);

//FORKS

int				create_forks(t_data *data);

//UTILS

int				ft_atoi(const char *str);
bool			ft_error_check(int argc, char **argv);

//ADMIN

void			hermes(t_data *data, t_philo *philo, char *msg, char *colour);
void			thanatos(t_data *data);

//THE TIME

long long		kronos(long long born_time);
bool			hypnos(long long sleep_time, t_philo *philo);

//FREE

int				morgan_freeman(t_data *data);

#endif