# Philosophers
[subject](https://github.com/tozggg/Philosophers/blob/master/subject.pdf)  
철학자 문제  
(프로세스 스레딩과 교착상태에 대한 해결 프로그램)
<br>
<br>
## Details
### 프로세스

- 실행중인 프로그램

### 스레드

- 프로세스의 실행단위 (=한 프로세스에서의 실행흐름)

### 뮤텍스

- 스레드가 소유할 수 있는 key로 공유자원에 대한 권한 관리 (한번에 한개의 스레드)

### 세마포어

- 공유자원에 접근할수 있는 스레드의 개수를 정해서 관리 (signal 사용)

### subject

```c
// 철학자의 상태
eating = 먹는중
thinking = 생각하는중(대기상태)
sleeping = 자는중(지연시간)

// 프로그램 옵션
number_of_philosophers = 철학자의 수
time_to_die = 철학자의 수명(이시간동안 안먹으면 사망..?)   //
time_to_eat = 밥을 먹는데 걸리는 시간                  // 밀리초 단위
time_to_sleep = 잠자는 시간                         //
(number_of_times_each_philosopher_must_eat = 철학자가 최소 밥을 먹어야 하는 횟수)

// 추가사항
철학자는 1~number_of_philosophers 의 고유번호 존재
한번에 한가지 행동만 가능
사망하면 시뮬레이션 종료
출력형식
출력 뒤엉키기 x
사망과 사망의 출력까지 10ms이하
```

### 허용함수
```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

memset
printf
malloc
free
write
usleep

int gettimeofday(struct timeval *tv, struct timezone *tz);
	tv.tv_sec = 초( * 1000000)
	tv.tv_usec = 마이크로초

// pthread
int pthread_create(phtread_t *thread, const phtread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	thread = 스레드식별자(스레드의 주소)
	attr = 스레드특성(보통 NULL)
	start_routine = 스레드 실행시 시작함수
	arg = 시작함수의 파라미터
	성공시 0을 리턴

int pthread_join(pthread_t th, void **thread_return);
	th스레드의 pthread_create 종료시 실행되며 해당함수 리턴값이 담기게된다

int phtread_detach(phtread_t th);

! join과 detach의 공통점과 차이점
공통점 = 스레드의 자원 반납
차이점 = join은 메인스레드에서 해당 스레드가 끝날때까지 대기 / detach는 같이 돈다

// mutex
! 한번에 하나의 스레드만 입장가능 (critical section)

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
	mutex 객체 초기화
	attr은 기본적으로 NULL

int pthread_mutex_destory(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
	한 스레드에서 lock시 unlock전까지 해당 코드구역 접근 불가
```
