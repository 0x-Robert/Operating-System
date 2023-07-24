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

### 출처 : Kocw 이화여대 반효경 교수 "운영체제" 강의 첨부

- http://www.kocw.net/home/search/kemView.do?kemId=1046323
