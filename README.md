# Operating-System

# 1. 운영체제 소개

### 운영체제란

- 운영체제 = 자원관리자
- 협의 운영체제 : 커널
- 광의 운영체제 : 커널뿐 아니라 주변 시스템 유틸리티 포함

### 운영체제의 목적

- 자원관리자

### 운영체제의 분류

#### 사용자의 수

- 단일 사용자 - MS-DOS
- 다중 사용자 - UNIX,NT Server

### 동시작업가능 여부

#### 실시간(realtime)

- Realtime OS 정해진 시간 안에 어떠한 일이 반드시 종료됨이 보장되어야하는 실시간 시스템을 위한 OS
- 원자로/공장 제어, 미사일 제어, 반도체 장비

### 처리 방식

#### 시분할(time sharing)

- 컴퓨터 처리능력을 일정한 시간단위로 분할해서 사용
- 일괄처리 시스템에 비해 짧은 응답 시간을 가짐
- 예) Unix
- interactive한 방식

#### 일괄처리(batch processing)

- 작업요청의 일정량을 모아서 한번에 처리
- 작업이 종료될떄까지 대기
- 예) 초기 Punch Card 처리 시스템

### 몇 가지 용어

- Multitasking
- Multiprogramming

- Time sharing
- Multiprocess
- 구분

  - 위의 용어들은 컴퓨터에서 여러 작업을 동시에 수행하는 것을 뜻한다.
  - Multiprogramming은 여러 프로그램이 메모리에 올라가 있음을 강조
  - Time Sharing은 CPU의 시간을 분할하여 나누어 쓴다는 의미를 강조
  - Multiprocessor : 하나의 컴퓨터에 CPU (processor)가 여러 개 붙어 있음을 의미

### 운영 체제의 예

#### 유닉스

- 코드의 대부분을 C언어로 작성
- 높은 이식성
- 최소한의 커널 구조
- 복잡한 시스템에 맞게 확장 용이
- 소스 코드 공개
- 프로그램 개발에 용이
- 다양한 버전
  - System V, FreeBSD, SunOS, Solaris
  - Linux

#### DOS

- MS사에서 1981년 IBM-PC를 위해 개발
- 단일 사용자용 운영체제, 메모리관리 능력의 한계(주 기억장치 : 640KB)

#### MS Windows

- MS사의 다중 작업용 GUI 기반 운영체제
- Plug and Play, 네트워크 환경 강화
- DOS용 응용 프로그램과 호환성 제공
- 불안정성
- 풍부한 지원 소프트웨어

#### Handheld device를 위한 OS

- PalmOS, Pocket PC(WinCE), Tiny OS

#### Apple Mac

#### Mobile (ios, Android)

### 운영체제의 구조

#### CPU 스케줄링 : 누구한테 CPU를 줄까 ?

#### 파일 관리 : 디스크에 파일을 어떻게 보관하지 ?

#### 메모리 관리 : 한정된 메모리를 어떻게 쪼개어 쓰지?

#### 입출력 관리 : 각기 다른 입출력장치와 컴퓨터 간에 어떻게 정보를 주고 받게 하지 ?

#### 프로세스관리 : 1. 프로세스의 생성과 삭제, 2. 자원 할당 및 반환, 3. 프로세스 간 협력

#### 그 외

- 보호 시스템
- 네트워킹
- 명령어 해석기 (command line interpreter)

```
본 과목은 OS 사용자 관점이 아니라 OS 개발자 관점에서 수강해야함
대부분의 알고리즘은 OS 프로그램 자체의 내용
인간의 신체가 뇌의 통제를 받듯 컴퓨터 하드웨어는 운영체제의 통제를 받으며 그 운영체제는 사람이 프로그래밍하는 것이다.

```

# 2. 시스템 구조와 프로그램 실행 (1)

- CPU : mode bit, Interrupt line, registers
- DMA controller
- timer
- memory controller - Memory
- device controller - local buffer - disk, i/o divice

### Mode bit

- 사용자 프로그램의 잘못된 수행으로 다른 프로그램 및 운영체제에 피해가 가지 않도록 하기 위한 보호 장치 필요

- Mode bit을 통해 하드웨어적으로 두 가지 모드의 operation 지원

* 1 사용자 모드 : 사용자 프로그램 수행
* 0 모니터모드(커널 모드, 시스템 모드)\* : OS 코드 수행

- 보안을 해칠 수 있는 중요한 명령어는 모니터 모드에서만 수행 가능한 "특권명령"으로 규정
- Interrupt나 Exception 발생시 하드웨어가 mode bit을 0으로 바꿈
- 사용자 프로그램에게 CPU를 넘기기 전에 mode bit을 1로 셋팅

### Timer

- 정해진 시간이 흐른 뒤 운영체제에게 제어권이 넘어가도록 인터럽트를 발생시킴
- 타이머는 매 클럭 틱 때마다 1씩 감소
- 타이머 값이 0이 되면 타이머 인터럽트 발생
- CPU를 특정 프로그램이 독점하는 것으로부터 보호

- 타이머는 time sharing을 구현하기 위해 널리 이용됨
- 타이머는 현재 시간을 계산하기 위해서도 사용

### Device Controller

- I/O device controller

* 해당 I/O 장치유형을 관리하는 일종의 작은 CPU
* 제어 정보를 위해 control register, status register를 가짐
* local buffer를 가짐(일종의 data register)
* I/O는 실제 device와 local buffer 사이에서 일어남
* Device controller는 I/O가 끝났을 경우 interrupt로 CPU에 그 사실을 알림

- device driver(장치 구동기) : OS 코드 중 각 장치별 처리 루틴 >> software
- device controller(장치제어기) : 각 장치를 통제하는 일종의 작은 CPU >> hardware

### 입출력(I/O)의 수행

- 모든 입출력 명령은 특권 명령
- 사용자 프로그램은 어떻게 I/O를 하는가 ?

* 시스템 콜 : 사용자 프로그램은 운영체제에게 I/O 요청
* trap을 사용하여 인터럽트 벡터의 특정 위치로 이동
* 제어권이 인터럽트 벡터가 가리키는 인터럽트 서비스 루틴으로 이동
* 올바른 I/O 요청인지 확인 후 I/O 수행
* I/O 완료 시 제어권을 시스템콜 다음 명령으로 옮김

### 인터럽트(Interrupt)

- 인터럽트 : 인터럽트 당한 시점의 레지스터와 program counter를 save한 후 CPU의 제어를 인터럽트 처리 루틴에 넘긴다.

- Interrupt(넓은의미)
- Interrupt(하드웨어 인터럽트) : 하드웨어가 발생시킨 인터럽트
- Trap(소프트웨어 인터럽트) : Exception(프로그램이 오류를 범한 경우), System call(프로그램이 커널 함수를 호출하는 경우)

- 인터럽트 관련 용어
- 인터럽트 벡터 : 해당 인터럽트의 처리 루틴 주소를 가지고 있음
- 인터럽트 처리 루틴 (Interrupt Service Routine, 인터럽트 핸들러), 해당 인터럽트를 처리하는 커널 함수

* 현대의 운영체제는 인터럽트에 의해 구동됨

### 시스템콜 ( System Call )

- 시스템콜
- 사용자 프로그램이 운영체제의 서비스를 받기 위해 커널 함수를 호출하는 것

# 3. 시스템 구조와 프로그램 실행 (2)

### 동기식 입출력과 비동기식 입출력

- 동기식 입출력(synchronous I/O)

  - I/O 요청 후 입출력 작업이 완료된 후에야 제어가 사용자 프로그램에 넘어감

  - 구현방법 1

    - I/O가 끝날 떄까지 CPU를 낭비시킴
    - 매시점 하나의 I/O만 일어날 수 있음

  - 구현방법 2

    - I/O가 완료될 때까지 해당 프로그램에게서 CPU를 빼앗음
    - I/O 처리를 기다리는 줄에 그 프로그램을 줄 세움
    - 다른 프로그램에게 CPU를 줌

- 비동기식 입출력 (asynchoronous I/O)

  - I/O가 시작된 후 입출력 작업이 끝나기를 기다리지 않고 제어가 사용자 프로그램에 즉시 넘어감

- 두 경우 모두 I/O의 완료는 인터럽트로 알려줌

### DMA (Direct Memory Access)

- 빠른 입출력 장치를 메모리에 가까운 속도로 처리하기 위해 사용
- CPU의 중재 없이 device controller가 device의 buffer storage의 내용을 메모리에
  block 단위로 직접 전송
- 바이트 단위가 아니라 block 단위로 인터럽트를 발생시킴

### 서로 다른 입출력 명령어

- I/O를 수행하는 special instruction에 의해
- Memory Mapped I/O에 의해

### 저장장치 계층 구조

Primary : Registers > Cache Memory > Main Memory
<br>
Secondary : Magnetic Disk > Optical Disk

Registers > Cache Memory > Main Memory > Magnetic Disk > Optical Disk

### 커널 주소 공간의 내용

- code : 커널코드
  - 시스템콜, 인터럽트 처리 코드
  - 자원관리를 위한 코드
  - 편리한 서비스 제공을 위한 코드
- data :
  - PCB-ProcessA, ProcessB
  - CPU
  - mem
  - disk
- stack
  - Process A의 커널 스택
  - Process B의 커널 스택

### 사용자 프로그램이 사용하는 함수

- 함수

  - 사용자 정의 함수 >> 프로세스A의 Address space(code, data, stack)

    - 자신의 프로그램에서 정의한 함수

  - 라이브러리 함수 >> 프로세스A의 Address space(code, data, stack)

    - 자신의 프로그램에서 정의하지 않고 갖다 쓴 함수
    - 자신의 프로그램의 실행 파일에 포함되어 있다.

  - 커널 함수 >> Kernel Address space(code, data, stack)

    - 운영체제 프로그램의 함수
    - 커널 함수의 호출 = 시스템 콜

### 프로그램의 실행

- program begins
- A의 주소공간 : user mode > user defined function call
- Kernel의 주소공간 : kernel mode > system call > return from kernel
- A의 주소공간 : user mode > library function call
- Kernel의 주소공간 : kernel mode > system call
- program ends

# 4. Process (1)

### 프로세스의 개념

- "Process is a program in execution"

- 프로세스의 문맥(context)
  - CPU 수행 상태를 나타내는 하드웨어 문맥
    - Program Counter
    - 각종 register
  - 프로세스의 주소 공간
    - code, data, stack
  - 프로세스 관련 커널 자료 구조
    - PCB (Process Control Block)
    - Kernel stack

### 프로세스의 상태 (Process State)

- Running

  - CPU를 잡고 instruction을 수행중인 상태

- Ready

  - CPU를 기다리는 상태(메모리 등 다른 조건을 모두 만족하고)

- Blocked(wait, sleep)

  - CPU를 주어도 당장 instruction을 수행할 수 없는 상태
  - Process 자신이 요청한 event(예 : I/O)가 즉시 만족되지 않아 이를 기다리는 상태
  - I/O등의 event를 스스로 기다리는 상태
  - (예) 디스크에서 file을 읽어와야 하는 경우

- Suspended (stopped)

  - 외부적인 이유로 프로세스의 수행이 정지된 상태
  - 프로세스는 통째로 디스크에 swap out된다.
  - (예) 사용자가 프로그램을 일시 정지시킨 경우 (break key)
    시스템이 여러 이유로 프로세스를 잠시 중단시킴
    (메모리에 너무 많은 프로세스가 올라와 있을 때)

- New : 프로세스가 생성중인 상태

- Terminated : 수행(execution)이 끝난 상태

- Blocked : 자신이 요청한 event가 만족되면 Ready

- Suspended : 외부에서 resume 해주어야 Active

### PCB (Process Control Block)

- 운영체제가 각 프로세스를 관리하기 위해 프로세스당 유지하는 정보
- 다음의 구성 요소를 가진다. (구조체로 유지)
  - (1) OS가 관리상 사용하는 정보
    - Process state, Process ID
    - scheduling information, priority
  - (2) CPU 수행 관련 하드웨어 값
    - Program counter, register
  - (3) 메모리 관련
    - Code, data, stack의 위치 정보
  - (4) 파일 관련
    - Open file descriptors..

### 문맥 교환 (Context Switch)

- CPU를 한 프로세스에서 다른 프로세스로 넘겨주는 과정
- CPU가 다른 프로세스에게 넘어갈 때 운영체제는 다음을 수행
  - CPU를 내어주는 프로세스의 상태를 그 프로세스의 PCB에 저장
  - CPU를 새롭게 얻는 프로세스의 상태를 PCB에서 읽어옴

* System call이나 interrupt 발생시 반드시 context switch가 일어나는 것은 아님

- A case

  - 1.  사용자 프로세스 A(user mode)
  - 2.  interrupt or system call
  - 3.  ISR or system call 함수(kernel mode)
  - 4.  문맥교환 없이 user mode 복귀
  - 5.  사용자 프로세스 A

- B case

  - 1. 사용자 프로세스 A(user mode)
  - 2. timer interrupt or I/O 요청 system call
  - 3. kernel mode
  - 4. 문맥교환 일어남
  - 5. 사용자 프로세스 B(user mode)

### 프로세스를 스케줄링하기 위한 큐

- Job queue
  - 현재 시스템 내에 있는 모든 프로세스의 집합
- Ready queue
  - 현재 메모리 내에 있으면서 CPU를 잡아서 실행되기를 기다리는 프로세스의 집합
- Device queues
  - I/O device의 처리를 기다리는 프로세스의 집합
- 프로세스들은 각 큐들을 오가며 수행된다.

### 스케줄러(Scheduler)

- Long-term scheduler (장기 스케줄러 or job scheduler)

  - 시작 프로세스 중 어떤 것들을 ready queue로 보낼지 결정
  - 프로세스에 memory(및 각종 자원)을 주는 문제
  - degree of Multiprogramming을 제어
  - time sharing system에는 보통 장기 스케줄러가 없음 (무조건 ready)

- Short-term scheduler(단기 스케줄러 or CPU scheduler)

  - 어떤 프로세스를 다음번에 running시킬지 결정
  - 프로세스에 CPU를 주는 문제
  - 충분히 빨라야 함(millisecond 단위)

- Medium-Term Scheduler(중기 스케줄러 or Swapper)

  - 여유 공간 마련을 위해 프로세스를 통째로 메모리에서 디스크로 쫓아냄
  - 프로세스에게서 memory를 뺏는 문제
  - degree of Multiprogramming을 제어

### Thread

- "A thread (or lightweight process) is basic unit of CPU utilization"
- Thread의 구성
  - program counter
  - register set
  - stack space
- Thread가 동료 thread와 공유하는 부분(=task)
  - code section
  - data section
  - OS resources
- 전통적인 개념의 heavyweight process는 하나의 thread를 가지고 있는 task로 볼 수 있다.

- 프로세스 주소공간 : Stack : (Thread1의 Stack, Thread2의 Stack, Thread3의 Stack), data, code
- 운영체제 내부에 프로세스 하나를 관리하기 위해 PCB를 가지고 있다.
- PCB (pointer, process state, process number, program counter, registers, memory limits, list of open files....)
- 프로세스는 하나만 띄워놓고(code, data, stack) CPU가 코드의 어느 부분을 실행하고 있는가(프로그램 카운터) 즉, 프로그램 카운터만 여러 개를 두는 것, 프로세스 하나에 CPU 수행단위만 여러개를 두는 것을 "Thread, 스레드"라고 한다.
- 스레드는 프로세스 하나에서 공유할 수 있는 것은 최대한 공유하고 (메모리를 공유하고, 프로세스 상태도 공유함)
- 스레드는 스택과 프로그램 카운터만 별도로 가지고 있다.

### Thread의 장점

- 다중 스레드로 구성된 태스크 구조에서는 하나의 서버 스레드가 blocked (waiting) 상태인 동안에도 동일한 태스크 내의 다른 스레드가 실행(running)되어 빠른 처리를 할 수 있다.
- 동일한 일을 수행하는 다중 스레드가 협력하여 높은 처리율(throughput)과 성능 향상을 얻을 수 있다.
- 스레드를 사용하면 병렬성을 높일 수 있다.
- 빠른 응답성을 가질 수 있다, 자원절약성을 가질 수 있다.

### Thread의 장점 2

- Responsiveness
  - eg) multi-threaded Web - if one thread is blocked (eg network), anther thread continues (eg display)
- Resource Sharing
  - n threads can share binary code, data, resource of the process
- Econnomy
  - creating & CPU switching thread (rather than a process)
  - Solaris의 경우 위 두 가지에 대해 프로세스의 overhead가 각각 30배, 5배
- Utilization of MP(멀티프로세서) Architectures
  - each thread may be running in parrel on a different processor

### Thread 구성

#### PCB

- 전체 KB(Process, heavyweight)

```
PCB
  {
    pointer, >> OS 관리용 정보
    process state, >> OS 관리용 정보
    process number, >> OS 관리용 정보
    <br>
    program counter, >> CPU 관련 정보(수 words)
    registers >> Thread, lightweight

    memory limits >> 자원 관련 정보
    list of open files >> 자원 관련 정보
  }
```

### Implementation of Threads

- Some are supported by kernel >> Kernel Threads

  - Windows 95/98/NT
  - Solaris
  - Digital UNIX, Mach

- Others are supported by library >> User Threads
  - POSIX Pthreads
  - Mach C-threads
  - Solaris threads
- Some are real-time threads

### 프로세스 생성(Process Creation)

Copy-on-write (CoW)

- 부모 프로세스(Parent process)가 자식 프로세스(children process) 생성
- 프로세스의 트리(계층 구조)형성
- 프로세스는 자원을 필요로 함
  - 운영체제로부터 받는다.
  - 부모와 공유한다.
- 자원의 공유
  - 부모와 자식이 모든 자원을 공유하는 모델
  - 일부를 공유하는 모델
  - 전혀 공유하지 않는 모델
- 수행(Execution)

  - 부모와 자식은 공존하며 수행되는 모델
  - 자식이 종료(terminate)될 때까지 부모가 기다리는(wait) 모델

- 주소공간 (Address space)
  - 자식은 부모의 공간을 복사함(binary and OS data)
  - 자식은 그 공간에 새로운 프로그램을 올림

* 유닉스의 예
  - fork() 시스템 콜(운영체제한테 부탁해서 생성되는 것)이 새로운 프로세스를 생성
    - 부모를 그대로 복사 (OS data except PID + binary)
    - 주소공간 할당
  - fork 다음에 이어지는 exec() 시스템 콜을 통해 새로운 프로그램을 메모리에 올림

### 프로세스 종료(Process Termination)

- 프로세스가 마지막 명령을 수행한 후 운영체제에게 이를 알려줌 (exit)
  - 자식이 부모에게 output data를 보냄 (via wait)
  - 프로세스의 각종 자원들이 운영체제에게 반납됨
- 부모 프로세스가 자식의 수행을 종료시킴(abort)
  - 자식이 할당 자원의 한계치를 넘어섬
  - 자식에게 할당된 태스크가 더 이상 필요하지 않음
  - 부모가 종료(exit)하는 경우
    - 운영체제는 부모 프로세스가 종료하는 경우 자식이 더 이상 수행되도록 두지 않는다.
    - 단계적인 종료

### fork() 시스템 콜

- A process is created by the fork() system call.

  - creates a new address space that is a duplicate of the caller

  ```c
  int main()
  {
    int pid;
    pid = fork();
    if (pid == 0) /* this is child*/
      printf("\n Hello, I am child!\n");
    else if (pid > 0) /* this is parent*/
      printf("\n Hello, I am parent!\n")
  }

  ```

### exec() 시스템 콜

- A process can execute a different program by the exec() system call.
  - replaces the memory image of the caller with a new program.

```c
int main()
{
  int pid;
  pid = fork();
  if (pid == 0) /* this  is child */
  {
    printf("\n Hello, I am child! Now I'll run date\n");
    execlp("/bin/date", "/bin/date", (char *)0);
  }
  else if (pid > 0) /* this is parent*/
    printf("\n Hello, I am parent!\n");
}

```

```c
int main()
{
  printf("1");
  execlp("echo", "echo", "3", (char *) 0); /* 1 , echo 출력*/
  printf("2");
}

```

### wait() 시스템 콜

- 프로세스 A가 wait() 시스템 콜을 호출하면
  - 커널은 child가 종료될 때까지 프로세스 A를 sleep 시킨다. (block 상태)
  - Child process가 종료되면 커널은 프로세스 A를 깨운다. (ready 상태)

```c
main()
{
  int childPID;
  s1;

  childPID = fork();

  if(childPID == 0 )
    <code for child process>
  else {
    wait();
  }

  s2;
}

```

### exit() 시스템 콜

- 프로세스의 종료

  - 자발적 종료

    - 마지막 statement 수행 후 exit() 시스템 콜을 통해
    - 프로그램에 명시적으로 적어주지 않아도 main함수가 리턴되는 위치에 컴파일러가 넣어줌

  - 비자발적 종료(외부에서 종료시킴, 부모프로세스나 사람이 종료 시킴)
    - 부모 프로세스가 자식 프로세스를 강제 종료시킴
      - 자식 프로세스가 한계치를 넘어서는 자원 요청
      - 자식에게 할당된 태스크가 더 이상 필요하지 않음
    - 키보드로 kill, break 등을 친 경우
    - 부모가 종료하는 경우
      - 부모 프로세스가 종료하기 전에 자식들이 먼저 종료됨.

### 프로세스와 관련한 시스템 콜

- fork() create a child(copy)

- exec() overlay new image

- wait() sleep until child is done

- exit() frees all the resources, notify parent

### 프로세스간 협력

- 독립적 프로세스(Independent process)

  - 프로세스는 각자의 주소 공간을 가지고 수행되므로 원칙적으로 하나의 프로세스는 다른 프로세스의 수행에 영향을 미치지 못함

- 협력 프로세스(Cooperating process)

  - 프로세스 협력 메커니즘을 통해 하나의 프로세스가 다른 프로세스의 수행에 영향을 미칠 수 있음

- 프로세스간 협력 메커니즘(IPC: Interprocess Communication)

  - 메시지를 전달하는 방법
    - message passing : 커널을 통해 메시지 전달
  - 주소 공간을 공유하는 방법

    - shared memory : 서로 다른 프로세스 간에도 일부 주소공간을 공유하게 하는 shared memory 메커니즘이 있음

    - thread : thread는 사실상 하나의 프로세스이므로 프로세스 간 협력으로\* 보기는 어렵지만 동일한 프로세스를 구성하는 thread간에는 주소공간을 공유하므로 협력이 가능

### Message Passing

- Message system

  - 프로세스 사이에 공유 변수(shared variable)를 일체 사용하지 않고 통신하는 시스템

- Direct Communication

  - 통신하려는 프로세스의 이름을 명시적으로 표시
  - Process P >>>> Process Q
    Send (Q, message) Receive(P, message)

- Indirect Communication
  - mailbox (또는 port)를 통해 메시지를 간접 전달
    Process P >> Mailbox >> M Process Q
    Send (M, message) Receive(M, message)

# 5. CPU Scheduling

### CPU and I/O Bursts in Program Execution

CPU burst : load store, add store, read from file
I/O burst : wait for I/O
CPU burst : store increment, index, write to file
I/O burst : wait for I/O
CPU burst : load store, add store, read from file
I/O burst : wait for I/O

### CPU-burst Time의 분포

- 여러 종류의 job(=process)가 섞여 있기 때문에 CPU 스케줄링이 필요하다.
- interactive job에게 적절한 response 제공 요망
- CPU와 I/O 장치 시스템 자원을 골고루 효율적으로 사용

### 프로세스의 특성 분류

- 프로세스는 그 특성에 따라 다음 두 가지로 나눔

  - I/O-bound process

    - CPU를 잡고 계산하는 시간보다 I/O에 많은 시간이 필요한 job
    - (many short CPU burst)

  - CPU-bound process
    - 계산 위주의 job
    - few very long CPU bursts

### CPU Scheduler & Dispatcher

- CPU Scheduler (운영체제코드, CPU 줄 프로세스를 고름)

  - Ready 상태의 프로세스 중에서 이번에 CPU를 줄 프로세스를 고른다.

- Dispatcher (운영체제코드, 선택된 프로세스에게 넘김)

  - CPU의 제어권을 CPU scheduler에 의해 선택된 프로세스에게 넘긴다.
  - 이 과정을 context switch(문맥 교환)이라고 한다.

* CPU 스케줄링이 언제 필요한가 ? (다음을 참고)

- CPU 스케줄링이 필요한 경우는 프로세스에게 다음과 같은 상태 변화가 있는 경우이다.

  - Running -> Blocked (예 : I/O 요청하는 시스템 콜)
  - Running -> Ready (예 : 할당시간만료 로 timer interrupt)
  - Blocked -> Ready (예 : I/O 완료 후 인터럽트)
  - Terminate

- 비선점형 1 ~ 4에서의 스케줄링은 nonpreemptive(=강제로 빼앗지 않고 자진 반납)
- 선점형 All other scheduling is preemptive(=강제로 빼앗음)

### Scheduling Criteria

#### Performance Index ( = Performance Measure, 성능 척도)

- CPU utilization(이용률) - 시스템 입장의 성능, 척도

  - keep the CPU as busy as possible

- Throughput(처리량) - 시스템 입장의 성능, 척도

  - of processes that complete their execution per time unit

- Turnaround time (소요시간, 반환시간) - 사용자 입장의 성능, 척도

  - amount of time to execute a particular process

- Waiting time (대기 시간) - 사용자 입장의 성능, 척도

  - amount of time a process has been waiting in the ready queue

- Response time (응답 시간) - 사용자 입장의 성능, 척도
  - amount of time it takes from when a request was submitted until the first response is produced. not output (for time-sharing environment)

### Scheduling Algorithms

- FCFS (First-Come First-Served)
- SJF (Shortest-Job-First)
- SRTF (Shortest-Remaining-Time-First)
- Priority Scheduling
- RR (Round Robin)
- Multilevel Queue
- Multilevel Feedback Queue

### FCFS (First-Come First-Served) (1)

- 예시 : 화장실 스케줄링(변비 있는 사람이 앞에서 화장실을 점유하고 있으면 아래 예시와 같은 일이 벌어진다.)

* 비선점형 스케줄링
  (선착순으로 동작하기 때문에 좋은 스케줄링은 아니다. 앞의 선착순으로 도착한 프로그램의 waiting시간에 따라 전체 waiting시간에 영향을 많이 준다.)

* Example

  - Process Burst Time
  - P1 24
  - P2 3
  - P3 3

* 프로세스의 도착 순서
* P1, P2, P3

  - P1(0-24)
  - P2(24-27)
  - P3(27-30)

* Wating time for P1 = 0; P2 = 24; P3 = 27
* Average wating time : (0 + 24 + 27 )/3 = 17

### FCFS (First-Come First-Served) (2)

- 프로세스의 도착순서가 다음과 같다고 하자.
- P2, P3, P1

  - P1(0-3)
  - P2(3-6)
  - P3(6-30)

- Waiting time for P1 = 6; P2 = 0; P3=3;
- Average waiting time : (6 + 0 + 3) /3 =3
- Much better than previous case
- Convoy effect : short process behind long process

### SJF (Shortest-Job-First)

- 각 프로세스의 다음번 CPU burst time을 가지고 스케줄링에 활용
- CPU burst time이 가장 짧은 프로세스를 제일 먼저 스케줄
- Two schemes :
  - Nonpreemptive 버전
    - 일단 CPU를 잡으면 이번 CPU burst가 완료될때까지 CPU를 선점(preemption) 당하지 않음
  - Preemptive 버전
    - 현재 수행중인 프로세스의 남은 burst time보다 더 짧은 CPU burst time을 가지는 새로운 프로세스가 도착하면 CPU를 빼앗김
    - 이 방법을 Shortest-Remaining-Time-First(SRTF)이라고도 부른다.
- SJF is optimal
  - 주어진 프로세스들에 대해 minimum average waiting time을 부정 (Preemptive 버전)

### Example of Non-Preemptive SJF

| Process | Arrival Time | Burst Time |
| ------- | ------------ | ---------- |
| P1      | 0.0          | 7          |
| P2      | 2.0          | 4          |
| P3      | 4.0          | 1          |
| P4      | 5.0          | 4          |
|         |              |            |

- SJF (non-preemptive)
  - P1(0-7)
  - P3(7-8)
  - P2(8-12)
  - P4(12-16)
- Average waiting time = (0 + 6 + 3 + 7)/4 = 4

### Example of Preemptive SJF

| Process | Arrival Time | Burst Time |
| ------- | ------------ | ---------- |
| P1      | 0.0          | 7          |
| P2      | 2.0          | 4          |
| P3      | 4.0          | 1          |
| P4      | 5.0          | 4          |
|         |              |            |

- SJF (preemptive)
  - P1(0-2)
  - P2(2-4)
  - P3(4-5)
  - P2(5-7)
  - P4(7-11)
  - P1(11-16)
- Average waiting time = (9 + 1 + 0 + 2)/4 = 3

### Priority Scheduling (우선순위 스케줄링)

- Priority number (integer) is associated with each process
- hightest priority를 가진 프로세스에게 CPU 할당
  (smallest integer = highest priority)
  - Preemptive
  - nonpreemptive
- SJF는 일종의 Priority scheduling이다.
  - priority = predicted next CPU burst time
- Problem
  - Starvation(기아 현상) low priority processes may never execute.
- Solution
  - Aging(노화) as time progresses increase the priority of the process.

### 다음 CPU Burst Time의 예측

- 다음번 CPU burst time을 어떻게 알 수 있는가 ? (input data, branch, user...)
- 추정(estimate)만이 가능하다.
- 과거의 CPU burst time을 이용해서 추정(예측)
  (exponential averaging)
  1. t[n](n번째 실제 CPU 사용시간) = actuallength of n^CPU burst
  2. r[n+1](타우, n+1번째 CPU 사용을 예측한 시간) - predicted value for the next CPU burst
  3. a(알파), 0 <= a(알파) <= 1
  4. Define : r[n+1] = a[tn] + (1-a)r[n]

### Round Robin (RR)

- 각 프로세스는 동일한 크기의 할당 시간(time quantum)을 가짐 (일반적으로 10-100 milliseconds)
- 할당 시간이 지나면 프로세스는 선점(preempted)당하고 ready queue의 제일 뒤에 가서 다시 줄을 선다.
- n개의 프로세스가 ready queue에 있고 할당 시간이 q time unit인 경우 각 프로세스는
  최대 q time unit 단위로 CPU 시간의 1/n을 얻는다.

  - 어떤 프로세스도 (n-1)q time unit 이상 기다리지 않는다.

- Performance
  - q large -> FCFS
  - q small -> context switch 오버헤드가 커진다.

### Example : RR with Time Quantum = 20

| Process | Burst Time |
| ------- | ---------- |
| P1      | 53         |
| P2      | 17         |
| P3      | 68         |
| P4      | 24         |
|         |            |

- The Gantt chart is :

| P1   | P2    | P3    | P4    | P1    | P3     | P4      | P1      | P3      | P3      |
| ---- | ----- | ----- | ----- | ----- | ------ | ------- | ------- | ------- | ------- |
| 0-20 | 20-37 | 37-57 | 57-77 | 77-97 | 97-117 | 117-121 | 121-134 | 134-154 | 154-162 |
|      |       |       |       |       |        |         |         |         |         |

- 일반적으로 SJF보다 average turnaround time이 길지만 response time은 더 짧다.

### Multilevel Queue

- Ready Queue를 여러 개로 분할
  - foreground (interactive)
  - background (batch - no human interaction)
- 각 큐는 독립적인 스케줄링 알고리즘을 가짐
  - foreground - RR
  - background - FCFS
- 큐에 대한 스케줄링이 필요
  - Fixed priority scheduling
    - serve all from foreground then from background
    - Possibility of starvation
  - Time slice
    - 각 큐에 CPU time을 적절한 비율로 할당
    - Eg., 80% to foreground in RR, 20% to background in FCFS

### Multilevel Queue (priority)

#### hightest priority

1. system processes
2. interactive processes
3. interactive editing processes
4. batch processes
5. student processes

#### lowest priority

### Multilevel Feedback Queue

- 프로세스가 다른 큐로 이동 가능
- 에이징(aging)을 이와 같은 방식으로 구현할 수 있다.
- Multilevel-feedback-queue scheduler를 정의하는 파라미터들
  - Queue의 수
  - 각 큐의 scheduling algorithm
  - Process를 상위 큐로 보내는 기준
  - Process를 하위 큐로 내쫓는 기준
  - 프로세스가 CPU 서비스를 받으려 할 때 들어갈 큐를 결정하는 기준

### Examples of Multilevel Feedback Queue

- Three queues

  - Q[0] - time quantum 8 milliseconds
  - Q[1] - time quantum 16 milliseconds
  - Q[2] - FCFS

- Scheduling
  - new job이 queue Q[0]로 들어감
  - CPU를 잡아서 할당 시간 8 milliseconds 동안 수행됨
  - 8 milliseconds 동안 다 끝내지 못했으면 queue Q[1]ㅡ로 내려감
  - Q[1]에 줄서서 기다렸다가 CPU를 잡아서 16ms동안 수행됨
  - 16ms에 끝내지 못한 경우 queue Q[2]로 쫓겨남

### Multiple-Processor Scheduling

- CPU가 여러 개인 경우 스케줄링은 더욱 복잡해짐
- Homogeneous processor인 경우
  - Queue에 한줄로 세워서 각 프로세서가 알아서 꺼내가게 할 수 있다.
  - 반드시 특정 프로세서에서 수행되어야 하는 프로세스가 있는 경우에는 문제가 더 복잡해짐
- Load sharing
  - 일부 프로세서에 job이 몰리지 않도록 부하를 적절히 공유하는 메커니즘 필요
  - 별개의 큐를 두는 방법 VS 공동 큐를 사용하는 방법
- Symmetric Multiprocessing (SMP)
  - 각 프로세서가 각자 알아서 스케줄링 결정
- Asymmetric multiprocessing
  - 하나의 프로세서가 시스템 데이터의 접근과 공유를 책임지고 나머지 프로세서는 거기에 따름

### Real-Time Scheduling

- Hard real-time systems
  - Hard real-time task는 정해진 시간 안에 반드시 끝내도록 스케줄링해야 함
- Soft real-time computing
  - Soft real-time task는 일반 프로세스에 비해 높은 priority를 갖도록 해야 함

### Thread Scheduling

- Local Scheduling
  - User level thread의 경우 사용자 수준의 thread library에 의해 어떤 thread를 스케줄할지 결정

* Global Scheduling
  - Kernel level thread의 경우 일반 프로세스와 마찬가지로 커널의 단기 스케줄러가 어떤 thread를 스케줄할지 결정

### Algorithm Evaluation

- Queueing models

  - 확률 분포로 주어지는 arrival rate와 service rate등을 통해 각종 performance index 값을 계산

- Implementation(구현) & Measurement(성능 측정)

  - 실제 시스템에 알고리즘을 구현하여 실제 작업(workload)에 대해서 성능을 측정 비교

- Simulation(모의 실험)
  - 알고리즘을 모의 프로그램으로 작성 후 trace를 입력으로 하여 결과 비교

# 6. Process Synchronization

### Race Condition

- S-box(Memory Address Space)를 공유하는 E-box(CPU Process)가 여럿 있는 경우 Race Condition의 가능성이 있음
  - Multiprocessor system
  - 공유메모리를 사용하는 프로세스들, 커널 내부데이터를 접근하는 루틴들 간
    (예 : 커널모드 수행 중 인터럽트로 커널모드 다른 루틴 수행시)

### OS에서 race condition은 언제 발생하는가 ?

1. kernel 수행 중 인터럽트 발생 시
2. Process가 system call을 하여 kernel mode로 수행중인데 context switch가 일어나는 경우
3. Multiprocessor에서 shared memory 내의 kernel data

### OS에서의 race condition(1/3)

- interrupt handler vs kernel

interrupt handler Count--
kernel Count++
(1. load, 2. Inc, 3. Store)

커널이 어떤 작업 중에 있을 때 인터럽트 요청이 와도 기존 작업을 다 한뒤에 인터럽트
처리 루틴으로 간다. 위와 같은 경우는 카운트가 1 증가함
커널에서 Count++ 작업 중 인터럽트로 Count--가 들어올 떄의 상황

- 커널모드 running 중 interrupt가 발생하여 인터럽트 처리루틴이 수행
  - 양쪽 다 커널 코드이므로 kernel address space 공유

### OS에서의 race condition(2/3)

1. user mode
2. System call
3. kernel mode
4. Return from kernel
5. user mode
6. System call
7. kernel mode

- 두 프로세스의 address space간에는 data sharing이 없음
- 그러나 system call을 하는 동안에는 kernel address space의 data를 access하게 됨(share)
- 이 작업 중간에 CPU를 preempt해가면 race condition 발생

### If you preempt CPU while in kernel mode ...

1. System call read()
2. Time quantum expires & P[B] needs CPU. P[A]는 CPU를 preempt 당함 (while in kernel !)
3. CPU 되돌려 받음

- 해결책 : 커널모드에서 수행중일때는 CPU를 preempt하지 않음 커널모드에서 사용자 모드로 돌아갈 때 preempt

### OS에서의 race condition(3/3)

어떤 CPU가 마지막으로 count를 store했는가 ? >>> race condition
multiprocessor의 경우 interrupt enable/disable로 해결되지 않음

- 방법1. 한번에 하나의 CPU만이 커널에 들어갈 수 있게 하는 방법
- 방법2. 커널 내부에 있는 각 공유 데이터에 접근할 때마다 그 데이터에 대한 lock / unlock을 하는 방법

# 6. Process Synchronization 2

### Process Synchronization 문제

- 공유 데이터(shared data)의 동시 접근(concurrent access)는 데이터의 불일치(inconsistency)를 발생시킬 수 있다.
- 일관성(consistency)유지를 위해서는 협력 프로세스(cooperating process)간의 실행 순서(orderly execution)을 정해주는 메커니즘 필요

- Race condition
  - 여러 프로세스들이 동시에 공유데이터를 접근하는 상황
  - 데이터의 최종 연산 결과는 마지막에 그 데이터를 다룬 프로세스에 따라 달라짐
- race condition을 막기 위해서는 concurrent process는 동기화(synchronize)되어야 한다.

### The Critical-Section Problem

- n개의 프로세스가 공유 데이터를 동시에 사용하기를 원하는 경우
- 각 프로세스의 code segment에는 공유데이터를 접근하는 코드인 critical section이 존재.
- Problem
  - 하나의 프로세스가 critical section에 있을 때 다른 모든 프로세스는 critical section에 들어갈 수 없어야 한다.

### Initial Attempts to Solve Problem

- 두 개의 프로세스가 있다고 가정 P[0], P[1]
- 프로세스들의 일반적인 구조

  ```c
  do {
    entry section
    critical section
    exit section
    remainder section
  }while(1);
  ```

* 프로세스들은 수행의 동기화(synchronize)를 위해 몇몇 변수를 공유할 수 있다.
  > > synchronization variable

### 프로그램적 해결법의 충족 조건

- Mutual Exclusion (상호배제)

  - 프로세스 Pi가 critical section 부분을 수행중이면 다른 모든 프로세스들은 그들의 critical section에 들어가면 안 된다.

- Progress(진행)

  - 아무도 critical section에 있지 않은 상태에서 critical section에 들어가고자 하는 프로세스가 있으면 critical section에 들어가게 해주어야 한다.

- Bounded Waiting(유한 대기)

  - 프로세스가 critical section에 들어가려고 요청한 후부터 그 요청이 허용될 때까지 다른 프로세스들이 critical section에 들어가는 횟수에 한계가 있어야 한다.

- 가정
  - 모든 프로세스의 수행 속도는 0보다 크다.
  - 프로세스들 간의 상대적인 수행 속도는 가정하지 않는다.

### Algorithm 1

- Synchronization variable
  int turn;
  initially turn = 0; >> P[i] can enter its critical section if (turn == i)
- Process P

  ```c
  do {
    while (turn != 0); /* My turn ? */
      critical section
      turn = 1;        /* Now it's your turn */
      remainder section
  } while(1);

  ```

* Satisfies mutual exclusion, but not progress
  - 즉, 과잉양보 : 반드시 교대로 들어가야만 함(swap-turn)
    그가 turn을 내 값으로 바꿔줘야만 내가 들어갈 수 있음 특정 프로세스가
    더 빈번히 criticial sectiovariables
    - n에 들어가야 한다면 ?

### Algorithm 2

- Synchronization variables
  - boolean flag[2];
    initially flag [모두] = false; /_no one is in CS_/
  - "P[1] ready to enter its critical section" (flag[i] == true)
- Process P[i]

  ```c
  do {
    flag[i] = true; /* Pretend I am in */
    while (flag[j]); /* Is he also in ? then wait */
    critical section
    flag[i] = false ; /* I am out now */
    remainder section
  } while(1);
  ```

  - Satisfies mutual exclusion, but not progress requirement.
  - 둘 다 2행까지 수행 후 끊임 없이 양보하는 상황 발생 가능

### Algorithm 3 (Peterson's Algorithm)

- Combined synchronization variables of algorithms 1 and 2
- Process P[i]

```c
do {
  flag [i] = true; /* My intention is to enter ... */
  turn = j;        /* Set to his turn */
  while(flag[j] && turn == j); /* wait only if ... */
  critical section
  flag[i] = false;
  remainder section
}while(1)
```

- Meets all three requirements; solves the critical section problem for two processes.
- Busy Waiting!(=spin lock!) (계속 CPU와 memory를 쓰면서 wait)

### Synchronization Hardware

- 하드웨어적으로 Test & modify를 atomic하게 수행할 수 있도록 지원하는 경우 앞의 문제는 간단히 해결
  - Test_and_set(a) 인스트럭션이 기존 값을 Read 하면서 새로 값을 설정하는 그런 기능을 한다.
    (1.Read, 2.TRUE )
- Mutual Exclusion with Test & Set

```c
Synchronization variable:
       boolean lock = false;

Process P[i]
        do {
          while (Test_and_Set(lock));
          critical section
          lock = false;
          remainder section
        }
```

# 6. Process Synchronization 3

### Semaphores

- 공유자원을 획득하고 반납하는 것을 처리해줌

* 앞의 방식들을 추상화시킴
* Semaphore S

  - integer variable
  - 아래의 두 가지 atomic 연산에 의해서만 접근 가능 (P 연산(공유데이터 획득), V 연산(공유데이터를 다 사용하고 반납하는 과정))

  ```c
  P(S) : while(S<=0) do no-op (i.e. wait)
         S--;

  If positive, decrement-&-enter.
  Otherwise, wait until positive (busy-wait)

  V(S) :
        S++;
  ```

### Critical Section of n Processes

```c
Synchronization variable
semaphore mutex; /* initially 1 : 1개가 CS에 들어갈 수 있다. */

Process P[i]
do {
  P(mutex);   /* If positive, dec-&-enter,Otherwise, wait. */
  critical section
  V(mutex);   /*  Increment semaphore */
  remainder section

} while(1);
```

- busy-wait은 효율적이지 못함(=spin lock)
- Block & Wakeup 방식의 구현 (=sleep lock) >> next page

### Block / Wakeup Implementation

- Semaphore를 다음과 같이 정의

```c
typedef struct
{
  int value; /* semaphore */
  struct process *L; /* process wait queue */
} semaphore;
```

- block과 wakeup을 다음과 같이 가정

  - block : 커널은 block을 호출한 프로세스를 suspend시킴 이 프로세스의 PCB를 semaphore에 대한 wait queue에 넣음
  - wakeup(P) : block된 프로세스 P를 wakeup 시킴 이 프로세스의 PCB를 ready queue로 옮김

  Semaphore : value-L >> PCB >> PCB >> PCB

### Implementation

- block/wakeup version of P() & V()

- Semaphore 연산이 이제 다음과 같이 정의됨

```c
P(S) : S.value--; /* prepare to enter */
       if (S.value < 0 ) /* Oops, negative, I cannot enter */
       {
          add this process to S.L;
          block();
       }
```

```c
V(S) : S.value++;
       if (S.value <= 0 ) {
          remove a process P from S.L;
          wakeup(P);
       }
```

### Which is better ?

- Busy-wait v.s. Block/wakeup

- Block/wakeup overhead v.s. Critical section 길이
  - Critical section의 길이가 긴 경우 Block/Wakeup이 적당
  - Critical section의 길이가 매우 짧은 경우 Block/Wakeup 오버헤드가 busy-wait 오버헤드보다 더 커질 수 있음
  - 일반적으로는 Block/wakeup 방식이 더 좋음

### Two Types of Semaphores

- Counting semaphore

  - 도메인이 0 이상인 임의의 정수값
  - 주로 resource counting에 사용

- Binary semaphore (=mutex)
  - 0 또는 1 값만 가질 수 있는 semaphore
  - 주로 mutual exclusion (lock/unlock) 사용

### Deadlock and Starvation

- Deadlock
  - 둘 이상의 프로세스가 서로 상대방에 의해 충족될 수 있는 event를 무한히 기다리는 현상
- S와 Q가 1로 초기화된 semaphore라 하자.

```
- P[0] P[1]
- P(S); P(Q); 하나씩 차지.
- P(Q); P(S); 상대방 것을 요구
- ..... .....
- V(S); V(Q); 여기와야 release함
- V(Q); V(S);
```

- Starvation
  - indefinite blocking. 프로세스가 suspend된 이유에 해당하는 세마포어 큐에서 빠져나갈 수 없는 현상.

# Process Synchronization 3

### Classical Problems of Synchronization

- Bounded-Buffer Problem (Producer-Consumer Problem)
- Readers and Writers Problem
- Dining-Philosophers Problem

### Bounded-Buffer Problem

#### (Producer-Consumer Problem)

#### Buffer in shared memory

#### Producer

1. Empty 버퍼가 있나요 ? (없으면 기다림)
2. 공유데이터에 lock을 건다.
3. Empty buffer에 데이터 입력 및 buffer 조작
4. Lock을 푼다.
5. Full buffer 하나 증가

#### Consumer

1. full 버퍼가 있나요 ? (없으면 기다림)
2. 공유데이터에 lock을 걸다.
3. Full buffer에서 데이터 꺼내고 buffer 조작
4. Lock을 푼다.
5. empty buffer 하나 증가.

#### Shared data

- buffer 자체 및 buffer 조작 변수(empty/full buffer의 시작 위치)

#### Synchronization variables

- mutual exclusion -> Need binary semaphore
  (shared data의 mutual exclusion을 위해)
- resource count -> Need integer semaphore
  (남은 full/empty buffer의 수 표시)

### Bounded-Buffer Problem

#### Synchronization variables

- semaphore full = 0, empty = n, mutex = 1;

#### Producer

```c
do {
  ...
  P(empty);
  P(mutex);
  ...
  add x to buffer
  ...
  V(mutex);
  V(full);
}while(1);
```

#### Consumer

```c
do {
  P(full)
  P(mutex);
  ...
  remove an item from buffer to y
  ...
  V(mutex);
  V(empty);
  ...
  consume the item in y
  ...
}while(1);
```

### Readers-Writers Problem (1)

- 한 process가 DB에 write 중일 때 다른 process가 접근하면 안됨
- read는 동시에 여럿이 해도 됨
- solution
  - Writer가 DB에 접근 허가를 아직 얻지 못한 상태에서는 모든 대기중인 Reader들을 다 DB에 접근하게 해준다.
  - Writer는 대기 중인 Reader가 하나도 없을 때 DB 접근이 허용된다.
  - 일단 Writer가 DB에 접근 중이면 Reader들은 접근이 금지된다.
  - Writer가 DB에서 빠져나가야만 Reader의 접근이 허용된다.

#### Shared data

- DB 자체
- readcount; /_ 현재 DB에 접근 중인 Reader의 수 _/

#### Synchronization variables

- mutex /_ 공유 변수 readcount를 접근하는 코드(critical section)의 mutual exclusion 보장을 위해 사용 _/
- db /_ Reader와 writer가 공유 DB 자체를 올바르게 접근하게 하는 역할 _/

### Readers-Writers Problem (2)

#### Shared data

int readcount = 0;
DB 자체;

Synchronization variables
semaphore mutex = 1, db = 1;

#### Writer

- P(db);
- ...
- writing DB is performed
- ...
- V(db)

---

#### Reader

- P(mutex);
- readcount++
- if(readcount==1)
- P(db); /_ block writer _/
- if (readcount == 1) /_ block writer _/
- V(mutex); /_readers follow_/
- ...
- reading DB is performed
- ...
- P(mutex);
- readcount--;
- if(readcount==0) V(db); /_enable writer_/
- V(mutex);

* ! Starvation 발생 가능

### Dining-Philosophers Problem

#### Synchronization variables

- semaphore chopstick[5]
  /_ Initially all values are 1 _/

#### Philosopher i

```c

do {
  P(chopstick[i]);
  P(chopstick[(i+1)%5]);
  ...
  eat();
  ...
  V(chopstick[i]);
  V(chopstick[(i+1)%5]);
  ...
  think();
  ...

}while(1);

```

### Dining-Philosophers Problem

- 앞의 solution의 문제점

  - Deadlock 가능성이 있다.
  - 모든 철학자가 동시에 배가 고파져 왼쪽 젓가락을 집어버린 경우

- 해결 방안
  - 4명의 철학자만이 테이블에 동시에 앉을 수 있도록 한다.
  - 젓가락을 두 개 모두 집을 수 있을때에만 젓가락을 집을 수 있게 한다.
  - 비대칭
    - 짝수(홀수) 철학자는 왼쪽(오른쪽) 젓가락부터 집도록

### Dining-Philosophers Problem

```c
enum {thinking, hungry, eating} state[5];
semaphore self[5]=0;
semaphore mutex=1;
```

#### Philosopher i

```c
do {
  pickup(i);
  eat();
  putdown(i);
  think();
}while(1);
```

```c
void putdown(int i){
  P(mutex);
  state[i] = thinking;
  test((i+4) % 5);
  test((i+4) % 5);
  V(mutex);
}
```

```c
void pickup(int i){
  P(mutex);
  state[i] = hungry;
  test(i);
  V(mutex);
  P(self[i]);
}
```

```c
void test(int i){
  if (state[(i+4)%5]!=eating && state[i]==hungry && state[(i+1)%5] != eating){
    state[i] = eating;
    V(self[i]);
  }
}
```

### Monitor

#### Semaphore의 문제점

- 코딩하기 힘들다.
- 정확성(correctness)의 입증이 어렵다.
- 자발적 협력(voluntary cooperation)이 필요하다.
- 한번의 실수가 모든 시스템에 치명적 영향

#### 예

- V(mutex) P(mutex)
- Critical Section Critical Section
- P(mutex) P(mutex)
  > > Mutual exclusion 깨짐 Deadlock

# Process Synchronization

- (프로세스 동기화)

# Concurrency Control

- (병행 제어)

### Monitor

#### 동시수행중인 프로세스 사이에서 abstract data type의 안전한 공유를 보장하기 위한 high-level synchronization construct

```c

monitor monitor-name
{
  shared variable declarations
  procedure body P[1](...){
    ...
  }

   procedure body P[2](...){
    ...
  }

   procedure body P[n](...){
    ...
  }
  {
    initialization code
  }
}

```

### Monitor

- 모니터 내에서는 한번에 하나의 프로세스만이 활동 가능
- 프로그래머가 동기화 제약 조건을 명시적으로 코딩할 필요없음
- 프로세스가 모니터 안에서 기다릴 수 있도록 하기 위해
  - condition variable 사용
    - condition x, y;
- Condition variable은 wait와 signal 연산에 의해서만 접근 가능

  - x.wait();

    - x.wait()을 invoke한 프로세스는 다른 프로세스가 x.signal()을 invoke하기 전까지 suspend된다.

  - x.signal();
    - x.signal()은 정확하게 하나의 suspend된 프로세스를 resume한다.
      - Suspend된 프로세스가 없으면 아무 일도 일어나지 않는다.

### Dining Philosophers Example

```c
monitor dining_philosopher
{
  enum {thinking, hungry, eating} state[5];
  condition self[5];
  void pickup(int i){
    state[i] = hungry;
    test(i);
    if (state[i] != eating)
        self[i].wait(); /* wait here*/
  }
}


void putdown(int i){
  state[i] = thinking;
  /* test left and right neighbors */
  test((i+4) % 5); /* if L is waiting */
  test((i+1) % 5);
}

void test(int i){
  if ( (state[(i+4) % 5] != eating) && (state[i] == hungry) && (state[(i+1) %5] != eating)){
    state[i] = eating;
    self[i].signal(); /*wake up Pi*/
  }
}

void init(){
  for(int i =0; i < 5;  i++)
    state[i] = thinking;
}

Each Philosopher:
  {
    pickup(i);
    eat();
    putdown(i);
    think();
  } while(1);
```

# 7. Deadlock

### The Deadlock Problem

#### Deadlock

- 일련의 프로세스들이 서로가 가진 자원을 기다리며 block된 상태

#### Resource (자원)

- 하드웨어, 소프트웨어 등을 포함하는 개념
- (예) I/O device, CPU cycle, memory space, semaphore 등
- 프로세스가 자원을 사용하는 절차
  - Request, Allocate, Use, Release

#### Deadlock Example 1

- 시스템에 2개의 tape drive가 있다.
- 프로세스 P[1]과 P[2] 각각이 하나의 tape drive를 보유한 채 다른 하나를 기다리고 있다.

#### Deadlock Example 2

- Binary semaphores A and B
  - P[0] : P[A], P[B]
  - P[1] : P[B], P[A]

### Deadlock 발생의 4가지 조건

#### Mutual exclusion

- 매 순간 하나의 프로세스만이 자원을 사용할 수 있음

#### No preemption

- 프로세스는 자원을 스스로 내어놓을 뿐 강제로 빼앗기지 않음

#### Hold and wait

- 자원을 가진 프로세스가 다른 자원을 기다릴 때 보유 자원을 놓지않고 계속 가지고 있음

#### Circular wait

- 자원을 기다리는 프로세스간에 사이클이 형성되어야함
- 프로세스 P[0], P[1], ..., P[n]이 있을 때
  - P[0]은 P[1]이 가진 자원을 기다림
  - P[1]은 P[2]이 가진 자원을 기다림
  - P[n-1]은 P[n]이 가진 자원을 기다림
  - P[n]은 P[0]이 가진 자원을 기다림

### Resource-Allocation Graph (자원할당 그래프) 1

#### Vertex

- Process P = {P[1], P[2], P[3]... P[n]}
- Resource R = {R[1],R[2], ... R[n]}

#### Edge

- request edge P[i] > R[j]
- assignment edge R[j] > P[i]

### Resource-Allocation Graph (자원할당 그래프) 2

#### 그래프에 cycle이 없으면 deadlock이 아니다.

#### 그래프에 cycle이 있으면

- if only one instance per resource type, then deadlock
- if several instances per resource type, possibility of deadlock

### Deadlock의 처리 방법

#### Deadlock Prevention

- 자원 할당시 Deadlock의 4가지 필요 조건 중 어느 하나가 만족되지 않도록 하는 것

#### Deadlock Avoidance

- 자원요청에 대한 부가적인 정보를 이용해서 deadlock의 가능성이 없는 경우에만 자원을 할당
- 시스템 state가 원래 state로 돌아올 수 있는 경우에만 자원 할당

#### Deadlock Detection and recovery

- Deadlock 발생은 허용하되 그에 대한 detection 루틴을 두어 deadlock 발견시 recover

#### Deadlock Ignorance

- Deadlock을 시스템이 책임지지 않음
- UNIX를 포함한 대부분의 OS가 채택

### Deadlock Prevention

#### Mutual Exclusion

- 공유해서는 안되는 자원의 경우 반드시 성립해야 함

#### Hold and WAit

- 프로세스가 자원을 요청할 때 다른 어떤 자원도 가지고 있지 않아야 한다.
- 방법 1. 프로세스 시작 시 모든 필요한 자원을 할당받게 하는 방법
- 방법 2. 자원이 필요할 경우 보유 자원을 모두 놓고 다시 요청

#### No Preemption

- process가 어떤 자원을 기다려야 하는 경우 이미 보유한 자원이 선점됨
- 모든 필요한 자원을 얻을 수 있을 때 그 프로세스는 다시 시작된다.
- State를 쉽게 save하고 restore할 수 있는 자원에서 주로 사용 (CPU, memory)

#### Circular Wait

- 모든 자원 유형에 할당 순서를 정하여 정해진 순서대로만 자원 할당
- 예를 들어 순서가 3인 자원 R[i]를 보유중인 프로세스가 순서가 1인 자원R[j]를 할당받기 위해서는 우선 R[i]를 release 해야한다.

> > > > Utilication 저하, throughput 감소, starvation 문제

### Deadlock Avoidance

#### Deadlock avoidance

- 자원 요청에 대한 부가정보를 이용해서 자원 할당이 deadlock으로 부터 안전(safe)한지를 동적으로 조사해서 안전한 경우에만 할당
- 가장 단순하고 일반적인 모델은 프로세스들이 필요로 하는 각 자원별 최대 사용량을 미리 선언하도록 하는 방법임

#### safe state

- 시스템 내의 프로세스들에 대한 safe sequence가 존재하는 상태

#### safe sequence

- 프로세스의 sequence <P[1], P[2], ... P[n]>이 safe하려면 P[i] (1<=i<=n)의
  자원 요청이 "가용 자원 + 모든 P[j](j<i)의 보유 자원"에 의해 충족되어야 함
- 조건을 만족하면 다음 방법으로 모든 프로세스의 수행을 보장
  - P[i]의 자원 요청이 즉시 충족될 수 없으면 모든 P[j](j<i)가 종료될 때까지 기다린다.
  * P[i-1]이 종료되면 P[i]의 자원 요청을 만족시켜 수행한다.

### Deadlock Avoidance

#### 시스템이 safe state에 있으면

- no deadlock

#### 시스템이 unsafe state에 있으면

- possibillity of deadlock

#### Deadlock Avoidance

- 시스템이 unsafe state에 들어가지 않는 것을 보장
- 2가지 경우의 avoidance 알고리즘
  - Single instance per resource types
    - Resource Allocation Graph algorithm 사용
  - Multiple instances per resource types
    - Banker's Algorithm 사용

### Banker's Algorithm

#### 가정

- 모든 프로세스는 자원의 최대 사용량을 미리 명시
- 프로세스가 요청 자원을 모두 할당받은 경우 유한 시간 안에 이들 자원을 다시 반납한다.

#### 방법

- 기본 개념 : 자원요청시 safe 상태를 유지할 경우에만 할당
- 총 요청 자원의 수가 가용 자원 수보다 적은 프로세스를 선택
  (그런 프로세스가 없으면 unsafe 상태)
- 그런 프로세스가 있으면 그 프로세스에게 자원을 할당
- 할당받은 프로세스가 종료되면 모든 자원을 반납
- 모든 프로세스가 종료될 때까지 이러한 과정 반복

### Example of Banker's Algorithm

#### 5 processes P[0], P[1], P[2], P[3], P[4]

#### 3 resource types A(10), B(5), C(7) instances

#### Snapshot at Time T[0]

|      | Allocation | Max   | Available | Need (Max - Allocation) |
| ---- | ---------- | ----- | --------- | ----------------------- |
|      | A B C      | A B C | A B C     | A B C                   |
| P[0] | 0 1 0      | 7 5 3 | 3 3 2     | 7 4 3                   |
| P[1] | 2 0 0      | 3 2 2 |           | 1 2 2                   |
| P[2] | 3 0 2      | 9 0 2 |           | 6 0 0                   |
| P[3] | 2 1 1      | 2 2 2 |           | 0 1 1                   |
| P[4] | 0 0 2      | 4 3 3 |           | 4 3 1                   |

- sequence < P[1], P[3], P[4], P[2],P[0]>가 존재하므로 시스템은 safe state

### Deadlock Detection and Recovery

#### Recovery

#### Process termination

- Abort all deadlocked processes
- Abort one processes at a time until the deadlock cycle is eliminated

#### Resource Preemption

- 비용을 최소화할 victim의 선정
- safe state로 rollback하여 process를 restart
- Starvation 문제
  - 동일한 프로세스가 계속해서 victim으로 선정되는 경우
  - cost factor에 rollback 횟수도 같이 고려

### Deadlock Ignorance

#### Deadlock이 일어나지 않는다고 생각하고 아무런 조치도 취하지 않음

- Deadlock이 매우 드물게 발생하므로 deadlock에 대한 조치 자체가 더 큰 overhead일 수 있음
- 만약, 시스템에 deadlock이 발생한 경우 시스템이 비정상적으로 작동하는 것을 느낀 후 직접 process를 죽이는 등의 방법으로 대처
- UNIX, Window 등 대부분의 범용 OS가 채택

# Memory Management (1)

### Logical vs. Physical Address

#### Logical address (=virtual address)

- 프로세스마다 독립적으로 가지는 주소 공간
- 각 프로세스마다 0번지부터 시작
- CPU가 보는 주소는 logical address임

#### Physical address

- 메모리에 실제 올라가는 위치

- 주소 바인딩 : 주소를 결정하는 것
  - Symbolic Address -> Logical Address -> Physical address
    (이 시점은 언제?, next page)

### 주소 바인딩 (Address Binding )

#### Compile time binding

- 물리적 메모리 주소(physical address)가 컴파일 시 알려짐
- 시작 위치 변경시 재컴파일
- 컴파일러는 절대 코드(absolute code) 생성

#### Load time binding

- Loader의 책임하에 물리적 메모리 주소 부여
- 컴파일러가 재배치가능코드(relocatable code)를 생성한 경우 가능

#### Execution time binding (=Run time binding)

- 수행이 시작된 이후에도 프로세스의 메모리 상 위치를 옮길 수 있음
- CPU가 주소를 참조할 때마다 binding을 점검(address mapping table)
- 하드웨어적인 지원이 필요(e.g., base and limit registers, MMU)

### 주소바인딩 (Address Binding)

- 소스코드(Symbolic address) > 컴파일 > 실행파일(Logical address) > 실행시작 > 물리적 메모리(Physical address)
- 물리적 메모리에 바인딩 하는 방법 : (Compile time binding, Load time binding, Run time binding)

### Memory-Management Unit

#### MMU(Memory-Management Unit)

- logical address를 physical address로 매핑해 주는 Hardware device

#### MMU scheme

- 사용자 프로세스가 CPU에서 수행되며 생성해내는 모든 주소값에 대해 base register(=relocation register)의 값을 더한다.

#### user program

- logical address만을 다룬다.
- 실제 physical address를 볼 수 없으며 알 필요가 없다.

### Hardware Support for Address Translation

- 운영체제 및 사용자 프로세스간의 메모리 보호를 위해 사용하는 레지스터
  - Relocation register : 접근할 수 있는 물리적 메모리 주소의 최소값 (=base register)
  - Limit register : 논리적 주소의; 범위

### Some Terminologies

1. Dynamic Loading

2. Dynamic Linking

3. Overlays

4. Swapping

### Dynamic Loading

- 프로세스 전체를 메모리에 미리 다 올리는 것이 아니라 해당 루틴이 불려질 때 메모리에 load 하는 것

* memory utilization의 향상

* 가끔식 사용되는 많은 양의 코드의 경우 유용

  - 예 : 오류 처리 루틴

* 운영체제의 특별한 지원 없이 프로그램 자체에서 구현 가능(OS는 라이브러리를 통해 지원 가능)

* Loading : 메모리로 올리는 것

### Overlays

- 메모리에 프로세스의 부분 중 실제 필요한 정보만을 올림
- 프로세스의 크기가 메모리보다 클 때 유용
- 운영체제의 지원없이 사용자에 의해 구현
- 작은 공간의 메모리를 사용하던 초창기 시스템에서 수작업으로 프로그래머가 구현
  - Manual Overlay
  - 프로그래밍이 매우 복잡

### Swapping

- Swapping
  - 프로세스를 일시적으로 메모리에서 backing store로 쫓아내는 것
- Backing store(=swap area)
  - 디스크
    - 많은 사용자의 프로세스 이미지를 담을 만큼 충분히 빠르고 큰 저장 공간
- Swap in / Swap out
  - 일반적으로 중기 스케줄러(swapper)에 의해 swap out 시킬 프로세스 선정
  - priority-based CPU scheduling algorithm
    - priority가 낮은 프로세스를 swapped out 시킴
    - priority가 높은 프로세스를 메모리에 올려 놓음
  - Compile time 혹은 load time binding에서는 원래 메모리 위치로 swap in 해야함
  - Execution time binding에서는 추후 빈 메모리 영역 아무 곳에나 올릴 수 있음
  - swap time은 대부분 transfer time(swap되는 양에 비례하는 시간)임

### Dynamic Linking

- Linking을 실행 시간(execution time)까지 미루는 기법
- Static linking
  - 라이브러리가 프로그램의 실행 파일 코드에 포함됨
  - 실행 파일의 크기가 커짐
  - 동일한 라이브러리를 각각의 프로세스가 메모리에 올리므로 메모리 낭비(eg. printf 함수의 라이브러리 코드)
- Dynamic linking
  - 라이브러리가 실행시 연결(link)됨
  - 라이브러리 호출 부분에 라이브러리 루틴의 위치를 찾기 위한 stub이라는 작은 코드를 둠
  - 라이브러리가 이미 메모리에 있으면 그 루틴의 주소로 가고 없으면 디스크에서 읽어옴
  - 운영체제의 도움이 필요

### Allocation of Physical Memory

- 메모리는 일반적으로 두 영역으로 나뉘어 사용

  - OS 상주 영역
    - interrupt vector와 함께 낮은 주소 영역 사용
  - 사용자 프로세스 영역
    - 높은 주소 영역 사용

- 사용자 프로세스 영역의 할당 방법
  - Contiguous allocation
    - 각각의 프로세스가 메모리의 연속적인 공간에 적재되도록 하는 것
      - Fixed partition allocation
      - Variable partition allocation
  - Noncontiguous allocation
    - 하나의 프로세스가 메모리의 여러 영역에 분산되어 올라갈 수 있음
      - Paging
      - Segmentation
      - Paged Segmentation

### Contiguous Allocation

- Contiguous allocation

  - 고정분할(Fixed partition) 방식

    - 물리적 메모리를 몇 개의 영구적 분할(partition)로 나눔
    - 분할의 크기가 모두 동일한 방식과 서로 다른 방식이 존재
    - 분할당 하나의 프로그램 적재
    - 융통성이 없음
      - 동시에 메모리에 load되는 프로그램의 수가 고정됨
      - 최대 수행 가능 프로그램 크기 제한
    - Internal fragmentation 발생(external fragmentation도 발생)

  - 가변분할(Variable partition) 방식
    - 프로그램의 크기를 고려해서 할당
    - 분할의 크기, 개수가 동적으로 변함
    - 기술적 관리 기법 필요
    - External fragmentation 발생

### Contiguous Allocation 2

- Hole
  - 가용 메모리 공간
  - 다양한 크기의 hole들이 메모리 여러 곳에 흩어져 있음
  - 프로세스가 도착하면 수용가능한 hole을 할당
  - 운영체제는 다음의 정보를 유지
    - a) 할당 공간
    - b) 가용 공간(hole)

### Contiguous Allocation 3

#### Dynamic Storage-Allocation Problem

- 가변 분할 방식에서 size n인 요청을 만족하는 가장 적절한 hole을 찾는 문제

  - First-fit
    - Size가 n 이상인 것 중 최초로 찾아지는 hole에 할당
  - Best-fit
    - Size가 n 이상인 가장 작은 hole을 찾아서 할당
    - Hole들의 리스트가 크기순으로 정렬되지 않은 경우 모든 hole의 리스트를 탐색해야함
    - 많은 수의 아주 작은 hole들이 생성됨
  - Worst-fit
    - 가장 큰 hole에 할당
    - 역시 모든 리스트를 탐색해야 함
    - 상대적으로 아주 큰 hole들이 생성됨

- First-fit과 best-fit이 worst-fit보다 속도와 공간 이용률 측면에서 효과적인 것으로 알려짐(실험적인 결과)

### Contiguous Allocation

- compaction
  - external fragmentation 문제를 해결하는 한 가지 방법
  - 사용 중인 메모리 영역을 한군데로 몰고 hole들을 다른 한 곳으로 몰아 큰 block을 만드는 것
  - 매우 비용이 많이 드는 방법임
  - 최소한의 메모리 이동으로 compactio하는 방법(매우 복잡한 문제)
  - Compaction은 프로세스의 주소가 실행 시간에 동적으로 재배치 가능한 경우에만 수행될 수 있다.

### Implementation of Page Table

- Page table은 main memory에 상주
- Page-table base register (PTBR)가 page table을 가리킴
- Page-table length register (PTLR)가 테이블 크기를 보관
- 모든 메모리 접근 연산에는 2번의 memory access 필요
- page table 접근 1번, 실제 data/instruction 접근 1번
- 속도 향상을 위해 associative register 혹은 translation look-aside buffer (TLB)라 불리는 고속의
  lookup hardware cache 사용

### Associative Register

- Associative registers (TLB) : parallel search가 가능
  - TLB에는 page table 중 일부만 존재.
- Address translation
  - page table 중 일부가 associative register에 보관되어있음
  - 만약 해당 page #가 associative register에 있는 경우 곧바로 frame#을 얻음
  - TLB는 context switch 때 flush (remove old entries)

### Effective Access Time

- Associative register lookup time = 엡실론
- memory cycle time = 1
- Hit ratio = 알파
  - associatvie register에서 찾아지는 비율
- Effective Access Time(EAT)

### Two-Level Page Table

- 현재의 컴퓨터는 address space가 매우 큰 프로그램 지원
  - 32 bit address 사용시 : 2^^32(4G)의 주소 공간
    - page size가 4K시 1M개의 page table entry 필요
    - 각 page entry가 4B시 프로세스당 4M의 page table 필요
    - 그러나, 대부분의 프로그램은 4G의 주소 공간 중 지극히 일부분만 사용하므로 page table 공간이 심하게 낭비됨
  - page table 자체를 page로 구성
  - 사용되지 않는 주소 공간에 대한 outer page table의 엔트리 값은 NULL(대응하는 inner page table이 없음)

### Two-Level Paging Example

- logical address (on 32-bit machine with 4K page size)의 구성

  - 20 bit의 page number
  - 12 bit의 page offset

- page table 자체가 page로 구성되기 때문에 page number는 다음과 같이 나뉜다.

  - 10-bit의 page number.
  - 10-bit의 page offset.

- 따라서 logical address는 다음과 같다.
  | page number | page offset |
  | ----|----|
  | p1 p2| d|
  | 10 10 | 12|

* P1은 outer page table의 index이고
* P2는 outer page table의 page에서의 변위(displacement)

### Multilevel Paging and Performance

- Address space가 더 커지면 다단계 페이지 테이블 필요
- 각 단계의 페이지 테이블이 메모리에 존재하므로 logical address의 physical address 변환에 더 많은 메모리 접근 필요
- TLB를 통해 메모리 접근 시간을 줄일 수 있음.
- 4단계 페이지 테이블을 사용하는 경우
  - 메모리 접근 시간이 100ns, TLB 접근 시간이 20ns이고
  - TLB hit ratio가 98%인 경우
    - effective memory access time = 0.98 _ 120 + 0.02 _ 520 = 128 nanoseconds.
- 결과적으로 주소변환을 위해 28ns만 소요

### Memory Protection

- Page table의 각 entry마다 아래의 bit를 둔다.

  - Protection bit
    - page에 대한 접근 권한 (read/write/read-only)
  - Valid-invalid bit

    - "valid"는 해당 주소의 frame에 그 프로세스를 구성하는 유효한 내용이 있음을 뜻함 (접근 허용)
    - "invalid"는 해당 주소의 frame에 유효한 내용이 없음\*을 뜻함(접근 불허)

    - "\*" i) 프로세스가 그 주소 부분을 사용하지 않는 경우
    - "\*" ii) 해당 페이지가 메모리에 올라와 있지 않고 swap area에 있는 경우

### Inverted Page Table

- page table이 매우 큰 이유

  - 모든 process별로 그 logical address에 대응하는 모든 page에 대해 page table entry가 존재.
  - 대응하는 page가 메모리에 있든 아니든 간에 page table에는 entry로 존재

- Inverted page table
  - Page frame 하나당 page table에 하나의 entry를 둔 것 (system-wide)
  - 각 page table entry는 각각의 물리적 메모리의 page frame이 담고 있는 내용 표시(process-id, process의 logical address)
  - 단점
    - 테이블 전체를 탐색해야함
  - 조치
    - associative register 사용 (expensive)

### Shared Page

- Shared code
  - Re-entrant Code (=Pure code)
  - read-only로 하여 프로세스 간에 하나의 code만 메모리에 올림(eg, text editors, compilers, window systems)
  - Shared code는 모든 프로세스의 logical address space에서 동일한 위치 있어야함
- Private code and data
  - 각 프로세스들은 독자적으로 메모리에 올림
  - Private data는 logical address space의 아무 곳에 와도 무방

### Segmentation

- 프로그램은 의미 단위인 여러 개의 segment로 구성
  - 작게는 프로그램을 구성하는 함수 하나하나를 세그먼트로 정의
  - 크게는 프로그램 전체를 하나의 세그먼트로 정의 가능
  - 일반적으로는 code, data, stack 부분이 하나씩의 세그먼트로 정의됨
- Segment는 다음과 같은 logical unit들임

```c
main(),
function,
global variables,
stack,
symbol table, arrays

```

### Segmentation Architecture

- Logical address는 다음의 두 가지로 구성

  - <segment-number, offset>

- Segment table
  - each table entry has:
    - base - starting physical address of the segment
    - limit - length of the segment
- Segment-table base register(STBR)
  - 물리적 메모리에서의 segment table의 위치
- Segment-table length register(STLR)
  - 프로그램이 사용하는 segment의 수
    - segment number s is legal if s < STLR

### Segmentation Architecture (Cont.)

- Protection
  - 각 세그먼트 별로 protection bit가 있음
  - Each entry:
    - Valid bit = 0 > illegal segment
    - Read/Write/Execution 권한 bit
- Sharing
  - shared segment
  - same segment number
  - segment는 의미단위이기 때문에 공유(sharing)과 보안(protection)에 있어 paging보다 훨씬 효과적이다.
- Allocation
  - first fit / best fit
  - external fragmentation 발생
  - segment의 길이가 동일하지 않으므로 가변분할 방식에서와 동일한 문제점들이 발생

### Segmentation with Paging

- pure segmentation과의 차이점
  - segment-table entry가 segment의 base address를 가지고 있는 것이 아니라 segment를 구성하는 page table의 base address를 가지고 있음

# 9. Virtual Memory

### Demand Paging

- 실제로 필요할 때 page를 메모리에 올리는 것
  - I/O 양의 감소
  - Memory 사용량 감소
  - 빠른 응답 시간
  - 더 많은 사용자 수용
- Valid / Invalid bit의 사용
  - Invalid의 의미
    - 사용되지 않은 주소 영역인 경우
    - 페이지가 물리적 메모리에 없는 경우
  - 처음에는 모든 page entry가 invalid로 초기화
  - address translation 시에 invalid bit이 set되어 있다면 >> "page fault"

### Page Fault

- invalid page를 접근하면 MMU가 trap을 발생시킴(page fault trap)
- Kernel mode로 들어가서 page fault handler가 invoke됨
- 다음과 같은 순서로 page fault를 처리한다.
  1.  Invalid reference ? (eg. bad address, protection violation) => abort process.
  2.  Get an empty page frame(없으면 뺏어온다: replace)
  3.  해당 페이지를 disk에서 memory로 읽어온다.
  - 3-1. disk I/O가 끝나기까지 이 프로세스는 CPU를 preempt 당함 (block)
  - 3-2. Disk read가 끝나면 page tables entry 기록, valid/invalid bit = "valid"
  - 3-3. ready queue에 process를 insert -> dispatch later
  4. 이 프로세스가 CPU를 잡고 다시 running
  5. 아까 중단되었던 instruction을 재개

### Performance of Demand Paging

- Page Fault Rate 0 <= p <= 1.0
  - if p = 0, no page faults
  - if p = 1, every reference is a fault
- Effective Access Time
  - =(1-p) \* memory access
  - +p (OS & HW page fault overhead)
  - +[swap page out if needed]
  - - swap page in
  - - OS & HW restart overhead

### Free frame이 없는 경우

- Page replacement

  - 어떤 frame을 빼앗아올지 결정해야 함
  - 곧바로 사용되지 않을 page를 쫓아내는 것이 좋음
  - 동일한 페이지가 여러 번 메모리에서 쫓겨났다가 다시 들어올 수 있음

- Replacement Algorithm
  - page-fault rate를 최소화하는 것이 목표
  - 알고리즘의 평가
    - 주어진 page reference string에 대해 page fault를 얼마나 내는지 조사
  - reference string의 예
    - 1,2,3,4,1,2,5,1,2,3,4,5.

### Page Replacement

1. swap out victim page
2. change to invalid (page table[frame, valid-invalid bit])
3. swap desired page in
4. reset page table for new page

### Optimal Algorithm

- MIN (OPT) : 가장 먼 미래에 참조되는 page를 replace
- 4 frames example
  - 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5
- 미래의 참조를 어떻게 아는가 ?
  - Offline algorithm
- 다른 알고리즘의 성능에 대한 upper bound 제공
  - Belady's optimal algorithm, MIN, OPT등으로 불림

### FIFO (First In First Out) Algorithm

- FIFO : 먼저 들어온 것을 먼저 내쫓음

  - 3 page frames : 9 page faults
  - 4 page frames : 10 page faults

- FIFO Anomaly (Belady's Anomaly)
  - more frames => less page faults

### LRU (Least Recently Used) Algorithm

- LRU : 가장 오래 전에 참조된 것을 지움

### LFU (Least Frequently Used) Algorithm

- LFU : 참조 횟수(reference count)가 가장 적은 페이지를 지움
  - 최저 참조 횟수인 page가 여럿 있는 경우
    - LFU 알고리즘 자체에서는 여러 page 중 임의로 선정한다.
    - 성능 향상을 위해 가장 오래전에 참조된 page를 지우게 구현 할수도 있다.
  - 장단점
    - LRU처럼 직전 참조 시점만 보는 것이 아니라 장기적인 시간 규모를 보기 때문에 page의 인기도를 좀 더 정확히 반영할 수 있음
    - 참조 시점의 최근성을 반영하지 못함
    - LRU보다 구현이 복잡함

### LRU와 LFU 알고리즘의 구현

- LRU : O(1) complexity (LRU page ~ MRU page)
- 최선 LPU : O(log n) complexity (LFU page ~ MRU page) - mean heap
- 최악 LPU : O(n) complexity (LFU page ~ MRU page, 한줄로 줄 세우기 할 때)

### 다양한 캐슁 환경

- 캐슁 기법
  - 한정된 빠른 공간(=캐쉬)에 요청된 데이터를 저장해 두었다가 후속 요청시 캐쉬로부터 직접 서비스하는 방식
  - paging system외에도 cache memory, buffer caching, Web caching 등 다양한 분야에서 사용
- 캐쉬 운영의 시간 제약
  - 교체 알고리즘에서 삭제할 항목을 결정하는 일에 지나치게 많은 시간이 걸리는 경우 실제 시스템에서 사용할 수 없음
  - Buffer caching이나 Web caching의 경우
    - O(1)에서 O(log n) 정도까지 허용
  - Paging system인 경우
    - page fault인 경우에만 OS가 관여함
    - 페이지가 이미 메모리에 존재하는 경우 참조시각등의 정보를 OS가 알 수 없음
    - O(1)인 LRU의 list조작조차 불가능

### Clock Algorithm

- Clock algorithm
  - LRU의 근사(approximation) 알고리즘
  - 여러 명칭으로 불림
    - Second chance algorithm
    - NUR(Not Used Recently) 또는 NRU(Not Recently Used)
  - Reference bit을 사용해서 교체 대상 페이지 선정 (circular list)
  - reference bit가 0인 것을 찾을 때까지 포인트를 하나씩 앞으로 이동
  - 포인터 이동하는 중에 reference bit 1은 모두 0으로 바꿈
  - Reference bit이 0인 것을 찾으면 그 페이지를 교체
  - 한 바퀴 되돌아와서도(=second chance) 0이면 그때에는 replace 당함
  - 자주 사용되는 페이지라면 second chance가 올 때 1
- Clock algorithm의 개선
  - reference bit과 modified bit (dirty bit)을 함께 사용
  - referce bit = 1 : 최근에 참조된 페이지
  - modified bit = 1 : 최근에 변경된 페이지(I/O를 동반하는 페이지)

### Page Frame의 Allocation

- Allocation problem : 각 process에 얼마만큼의 page frame을 할당할 것인가 ?
- Allocation의 필요성 :
  - 메모리 참조 명령어 수행시 명령어, 데이터 등 여러 페이지 동시 참조
    - 명령어 수행을 위해 최소한 할당되어야 하는 frame의 수가 있음
  - Loop를 구성하는 page들은 한꺼번에 allocate 되는 것이 유리함
    - 최소한의 allocation이 없으면 매 loop마다 page fault
- Allocation Scheme
  - Equal allocation : 모든 프로세스에 똑같은 갯수 할당
  - Proportional allocation : 프로세스 크기에 비례하여 할당
  - Priority allocation : 프로세스의 priority에 따라 다르게 할당

### Global vs. Local Replacement

#### Global replacement

- Replace시 다른 process에 할당된 frame을 빼앗아 올 수 있다.
- Process별 할당량을 조절하는 또 다른 방법임
- FIFO, LRU, LFU 등의 알고리즘을 global replacement로 사용시에 해당
- Working set, PFF 알고리즘 사용

#### Local replacement

- 자신에게 할당된 frame 내에서만 replacement
- FIFO, LRU, LFU 등의 알고리즘을 process별로 운영시

### Thrashing

- 프로세스의 원활한 수행에 필요한 최소한의 page frame 수를 할당 받지 못한 경우 발생
- Page fault rate이 매우 높아짐
- CPU utilization이 높아짐
- OS는 MPD (Multiprogramming degree)를 높여야 한다고 판단
- 또 다른 프로세스가 시스템에 추가됨 (higher MPD)
- 프로세스 당 할당된 frame의 수가 더욱 감소
- 프로세스는 page의 swap in / swap out으로 매우 바쁨
- 대부분의 시간에 CPU는 한가함
- low throughput

### Working-Set Model

#### Locality of reference

- 프로세스는 특정 시간동안 일정 장소만을 집중적으로 참조한다.
- 집중적으로 참조되는 해당 page들의 집합을 locality set이라 함.

#### Working-set Model

- Locality에 기반하여 프로세스가 일정 시간동안 원활하게 수행되기 위해 한꺼번에 메모리에 올라와 있어야 하는 page들의 집합을 Working Set이라 정의함
- Working Set 모델에서는 process의 working set 전체가 메모리에 올라와 있어야 수행되고 그렇지 않을 경우 모든 frame을 반납한 후 swap out (suspend)
- Thrashing을 방지함
- Multiprogramming degree를 결정함

### Working-Set Algorithm

- Working set의 결정
  - Working set window를 통해 알아냄
  - window size가 델타인 경우
    - 시각 t[i]에서의 working set WS (t[i])
      - Time interval[t[i]-델타, t[i]] 사이에 참조된 서로 다른 페이지들의 집합
      - Working set에 속한 page는 메모리에 유지, 속하지 않은 것은 버림
      * (즉, 참조된 후 델타 시간동안 해당 page를 메모리에 유지한 후 버림)

### Working-Set Algorithm

#### Working-Set Algorithm

- Process들의 working set size의 합이 page frame의 수보다 큰 경우
  - 일부 process를 swap out시켜 남은 process의 working set을 우선적으로 충족시켜 준다. (MPD를 줄임)
- Working set을 다 할당하고도 page frame이 남는 경우
  - Swap out 되었던 프로세스에게 working set을 할당 (MPD를 키움)

#### Window size 델타

- Working set을 제대로 탐지하기 위해서는 window size를 잘 결정해야 함
- 델타 값이 너무 작으면 locality set을 모두 수용하지 못할 우려
- 델타 값이 크면 여러 규모의 locality set 수용
- 델타값이 무한대면 전체 프로그램을 구성하는 page를 working set으로 간주

### PFF (Page-Fault Frequency) Scheme

- page-fault rate의 상한값과 하한값을 둔다.
  - Page fault rate이 상한값을 넘으면 frame을 더 할당한다.
  - Page fault rate이 하한값 이하이면 할당 frame 수를 줄인다.
- 빈 frame이 없으면 일부 프로세스를 swap out

### Page Size의 결정

- Page size를 감소시키면

  - 페이지 수 증가
  - 페이지 테이블 크기 증가
  - Internal fragmentation 감소
  - Disk transfer의 효율성 감소
    - Seek/rotation vs. transfer
  - 필요한 정보만 메모리에 올라와 메모리 이용이 효율적

    - Locality의 활용 측면에서는 좋지 않음

- Trend
  - Larger page size

# File Systems

### File and File System

#### File

- "A named collection of related information"
- 일반적으로 비휘발성의 보조기억장치에 저장
- 운영체제는 다양한 저장장치를 file이라는 동일한 논리적 단위로 볼 수 있게 해줌
- Operation
  - create, read, write reposition (lseek), delete, open, close 등

#### File attribute(혹은 파일의 metadata)

- 파일 자체의 내용이 아니라 파일을 관리하기 위한 정보들
- 파일 이름, 유형, 저장된 위치, 파일 사이즈
- 접근 권한(읽기/쓰기/실행), 시간 (생성/변경/사용), 소유자 등

#### File system

- 운영체제에서 파일을 관리하는 부분
- 파일 및 파일의 메타데이터, 디렉토리 정보등을 관리
- 파일의 저장 방법 결정
- 파일 보호 등

### Directory and Logical Disk

#### Directory

- 파일의 메타데이터 중 일부를 보관하고 있는 일종의 특별한 파일
- 그 디렉토리에 속한 파일 이름 및 파일 attribute들
- operation
  - search for a file, create a file, delete a file
  - list a directory, rename a file, traverse the file system

#### Partition(=Logical Disk)

- 하나의 (물리적) 디스크 안에 여러 파티션을 두는게 일반적
- 여러 개의 물리적인 디스크를 하나의 파티션으로 구성하기도 함
- (물리적) 디스크를 파티션으로 구성한 뒤 각각의 파티션에 file system을 깔거나 swapping등 다른 용도로 사용할 수 있음

### Open()

#### open("a/b/c")

- 디스크로부터 파일 c의 메타데이터를 메모리로 가지고 옴
- 이를 위하여 directory path를 search
  - 루트 디렉토리 "/"를 open하고 그 안에서 파일 "a"의 위치 획득
  - 파일 "a"를 open한 후 read하여 그 안에서 파일 "b"의 위치 획득
  - 파일 "b"를 open한 후 read하여 그 안에서 파일 "c"의 위치 획득
  - 파일 "c"를 open한다.
- Directory path의 search에 너무 많은 시간 소요
  - Open을 read / write와 별도로 두는 이유임
  - 한번 open한 파일은 read/write시 directory seach 불필요
- Open file table
  - 현재 open된 파일들의 메타데이터 보관소 (in memory)
  - 디스크의 메타데이터보다 몇 가지 정보가 추가
    - open한 프로세스의 수
    - File offset : 파일 어느 위치 접근중인지 표시(별도 테이블 필요)
- File descripter (file handle, file control block)
  - Open file table에 대한 위치 정보 (프로세스 별)

### File Protection

- 각 파일에 대해 누구에게 어떤 유형의 접근(read/write/execution)을 허락할 것인가?

#### Access Control 방법

- Access control list : 파일별로 누구엑 어떤 접근 권한이 있는지 표시
- Capability : 사용자별로 자신이 접근 권한을 가진 파일 및 해당 권한 표시

#### Grouping

- 전체 user를 owner, group, public의 세 그룹으로 구분
- 각 파일에 대해 세 그룹의 접근 권한(rwx)를 3비트씩으로 표시
- 예) Unix (owner | group | other)

#### Password

- 파일마다 password를 두는 방법(디렉토리 파일에 두는 방법도 가능)
- 모든 접근 권한에 대해 하나의 password : all-or-nothing
- 접근 권한별 password : 암기 문제, 관리 문제

### Access Methods

#### 시스템이 제공하는 파일 정보의 접근 방식

- 순차 접근(sequential access)
  - 카세트 테이프를 사용하는 방식처럼 접근
  - 읽거나 쓰면 offset은 자동적으로 증가
- 직접 접근(direct access, random access)
  - LP 레코드 판과 같이 접근하도록 함
  - 파일을 구성하는 레코드를 임의의 순서로 접근할 수 있음

# 11. File System Implementation

### Allocation of File Data in Disk

- Contiguous Allocation
- Linked Allocation
- Indexed Allocation

### Contiguous Allocation

- 단점
  - external fragmentation
  - File grow가 어려움
    - file 생성시 얼마나 큰 hole을 배당할 것인가 ?
    - grow 가능 vs 낭비 (internal fragmentation)
- 장점
  - Fast I/O
    - 한번의 seek/rotation으로 많은 바이트 transfer
    - Realtime file용으로, 또는 이미 run 중이던 process의 swapping
  - Direct access(=random access) 가능

### Linked Allocation

- 장점
  - External fragmentation 발생 안 함
- 단점

  - No random access
  - Reliability 문제
    - 한 sector가 고장나 pointer가 유실되면 많은 부분을 잃음
  - Pointer를 위한 공간이 block의 일부가 되어 공간 효율성을 떨어뜨림
    - 512 bytes/secore, 4bytes/pointer

- 변형
  - File-allocation table(FAT) 파일 시스템
    - 포인터를 별도의 위치에 보관하여 reliability와 공간효율성 문제 해결

### Indexed Allocation

- 장점
  - External fragmentatio이 발생하지 않음
  - Direct access 가능
- 단점
  - Small file의 경우 공간 낭비(실제로 많은 file들이 small)
  - Too Large file의 경우 하나의 block으로 index를 저장하기에 부족
    - 해결방안
      - 1. linked scheme
      - 2. multi-level index

### Unix 파일시스템의 구조

```c
Partition
  {
  Boot block,
  Super block,
  []Inode list,
  Data block
  }

```

```c
Inode list
{
  mode,
  owners(2),
  timestamps(3),
  size block,
  count,
  direct blocks [data....],
  single indirect,
  double indirect,
  triple indirect
}
```

### Unix 파일시스템의 구조

#### 유닉스 파일 시스템의 중요 개념

- Boot block
  - 부팅에 필요한 정보 (bootstrap loader)
- Superblock
  - 파일시스템에 관한 총체적인 정보를 담고 있다.
- Inode
  - 파일 이름을 제외한 파일의 모든 메타 데이터를 저장
- Data block
  - 파일의 실제 내용을 보관

### Free-Space Management

#### Bit map or bit vector

```c
bit[i] = {
  0 => block[i] free
  1 => block[i] occupied
}
```

- Bit map은 부가적인 공간을 필요로 함
- 연속적인 n개의 free block을 찾는데 효과적

### Free-Space Management

- Linked list

  - 모든 free block들을 링크로 연결 (free list)
  - 연속적인 가용공간을 찾는 것은 쉽지 않다.
  - 공간의 낭비가 없다.

- Grouping
  - linked list 방법의 변형
  - 첫번째 free block이 n개의 pointer를 가짐
    - n-1 pointer는 free data block을 가리킴
    - 마지막 pointer가 가리키는 block은 또 다시 n pointer를 가짐
- Counting
  - 프로그램들이 종종 여러 개의 연속적인 block을 할당하고 반납한다는 성질에 착안
  - (first free block, # of contiguous free blocks)을 유지

### Directory Implementation

- Linear list

  - <file name, file의 metadata>의 list
  - 구현이 간단
  - 디렉토리 내에 파일이 있는지 찾기 위해서는 linear search 필요 (time-consuming)

- Hash Table
  - linear list + hashing
  - Hash table은 file name을 이 파일의 linear list의 위치로 바꾸어줌
  - search time을 없앰
  - Collision 발생 가능

### VFS and NFS

- Virtual File System(VFS)

  - 서로 다른 다양한 file system에 대해 동일한 시스템 콜 인터페이스(API)를 통해 접근할 수 있게 해주는 OS의 layer

- Network File System(NFS)
  - 분산 시스템에서는 네트워크를 통해 파일이 공유될 수 있음
  - NFS는 분산 환경에서의 대표적인 파일 공유 방법임

### Page Cache and Buffer Cache

- Page Cache
  - Virtual memory의 paging system에서 사용하는 page frame을 caching의 관점에서 설명하는 용어
  - Memory-Mapped I/O를 쓰는 경우 file의 I/O에서도 page cache 사용
- Memory-Mapped I/O
  - File의 일부를 virtual memory에 mapping시킴
  - 매핑시킨 영역에 대한 메모리 접근 연산은 파일의 입출력을 수행하게 함
- Buffer Cache
  - 파일시스템을 통한 I/O 연산은 메모리의 특정 영역인 buffer cache 사용
  - File 사용의 locality 활용
    - 한번 읽어온 block에 대한 후속 요청시 buffer cache에서 즉시 전달
  - 모든 프로세스가 공용으로 사용
  - Replacement algorithm 필요 (LRU, LFU 등)
- Unified Buffer Cache
  - 최근의 OS에서는 기존의 buffer cache가 page cache에 통합됨

# 12. Disk Management and Scheduling

### Disk Structure

- logical block
  - 디스크의 외부에서 보는 디스크의 단위 정보 저장 공간들
  - 주소를 가진 1차원 배열처럼 취급
  - 정보를 전송하는 최소 단위
- Sector
  - Logical block이 물리적인 디스크에 매핑된 위치
  - Sector 0은 최외곽 실린더의 첫 트랙에 있는 첫 번째 섹터이다.

### Disk Scheduling

- Access time의 구성
  - Seek time
    - 헤드를 해당 실린더로 움직이는데 걸리는 시간
  - Rotational latency
    - 헤드가 원하는 섹터에 도달하기까지 걸리는 회전지연시간
  - Transfer time
    - 실제 데이터의 전송 시간
- Disk bandwith
  - 단위 시간 당 전송된 바이트의 수
- Disk Scheduling
  - seek time을 최소화하는 것이 목표
  - Seek time ~ seek distance

### Disk Management

- physical formatting (Low-level formatting)

  - 디스크를 컨트롤러가 읽고 쓸 수 있도록 섹터들로 나누는 과정
  - 각 섹터는 header + 실제 data(보통 512 bytes) + trailer로 구성
  - header와 trailer는 sector number, ECC (Error-Correcting Code) 등의 정보가 저장되며 controller가 직접 접근 및 운영

- Partitioning
  - 디스크를 하나 이상의 실린더 그룹으로 나누는 과정
  - OS는 이것을 독립적 disk로 취급(logical disk)
- Logical formatting
  - 파일 시스템을 만드는 것
  - FAT, inode, free space 등의 구조 포함
- Booting
  - ROM에 있는 "small bootstrap loader"의 실행
  - sector 0 (boot block)을 load하여 실행
  - sector 0은 "full Bootstrap loader program"
  - OS를 디스크에서 load하여 실행

### Disk Scheduling Algorithm

- 큐에 다음과 같은 실린더 위치의 요청이 존재하는 경우 디스크 헤드 53번에서 시작한 각 알고리즘의 수행 결과는 ?

* 98, 183, 37, 122, 14, 124, 65, 67

- FCFS
- SSTF
- SCAN
- C-SCAN
- N-SCAN
- LOOK
- C-LOOK

### FCFS(First Come First Service)

- 총 head의 이동 : 640 cylinders
- head starts at 53

### SSTF (Shortest Seek Time First)

- starvation 문제
- 총 head의 이동 : 236 cylinders

### SCAN

- disk arm이 디스크의 한쪽 끝에서 다른쪽 끝으로 이동하며 가는 길목에 있는 모든 요청을 처리한다.
- 다른 한쪽 끝에 도달하면 역방향으로 이동하며 오는 길목에 있는 모든 요청을 처리하며 다시 반대쪽 끝으로 이동한다.
- 문제점 : 실린더 위치에 따라 대기 시간이 다르다.

### SCAN

- 총 head의 이동 : 208 cylinders

### C-SCAN

- 헤드가 한쪽 끝에서 다른쪽 끝으로 이동하며 가는 길목에 있는 모든 요청을 처리
- 다른쪽 끝에 도달했으면 요청을 처리하지 않고 곧바로 출발점으로 다시 이동
- SCAN보다 균일한 대기 시간을 제공한다.

### Other Algorithm

- N-SCAN
  - SCAN의 변형 알고리즘
  - 일단 arm이 한 방향으로 움직이기 시작하면 그 시점이후에 도착한 job은 되돌아올 때 service
- LOOK and C-LOCK
  - SCAN이나 C-SCAN은 헤드가 디스크 끝에서 끝으로 이동
  - LOOK과 C-LOOK은 헤드가 진행중이다가 그 방향에 더이상 기다리는 요청이 없으면 헤드의 이동방향을 즉시 반대로 이동

### Disk-Scheduling Algorithm의 결정

- SCAN, C-SCAN 및 그 응용 알고리즘은 LOOK, C-LOOK 등이 일반적으로 디스크 입출력이 많은 시스템에서 효율적인 것으로 알려져 있음
- File의 할당 방법에 따라 디스크 요청이 영향을 받음
- 디스크 스케줄링 알고리즘은 필요할 경우 다른 알고리즘으로 쉽게 교체할 수 있도록 OS와 별도의 모듈로 작성되는 것이 바람직하다.

### Swap-Space Management

- Disk를 사용하는 두 가지 이유
  - memory의 volatile한 특성 > file system
  - 프로그램 실행을 위한 memory공간 부족 > swap space(swap area)
- Swap-space
  - Virtual memory system에서는 디스크를 memory의 연장 공간으로 사용
  - 파일시스템 내부에 둘 수도 있으나 별도 partition 사용이 일반적
    - 공간효율성보다는 속도 효율성이 우선
    - 일반 파일보다 훨씬 짧은 시간만 존재하고 자주 참조됨
    - 따라서, block의 크기 및 저장 방식이 일반 파일시스템과 다름

### RAID

- RAID(Redundant Array of Independent Disks)
  - 여러 개의 디스크를 묶어서 사용
- RAID의 사용 목적
  - 디스크 처리 속도 향상
    - 여러 디스크에 block의 내용을 분산 저장
    - 병렬적으로 읽어옴 (interleaving, striping)
  - 신뢰성(reliability) 향상
    - 동일 정보를 여러 디스크에 중복 저장
    - 하나의 디스크가 고장(failure)시 다른 디스크에서 읽어옴(Mirroring, shadowing)
    - 단순한 중복 저장이 아니라 일부 디스크에 parity를 저장하여 공간의 효율성을 높일 수 있다.

### 출처 : Kocw 이화여대 반효경 교수 "운영체제" 강의 첨부

- http://www.kocw.net/home/search/kemView.do?kemId=1046323
