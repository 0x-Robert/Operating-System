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

### 출처 : Kocw 이화여대 반효경 교수 "운영체제" 강의 첨부

- http://www.kocw.net/home/search/kemView.do?kemId=1046323
