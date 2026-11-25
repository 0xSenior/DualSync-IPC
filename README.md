# DualSync-IPC

> A low-level dual-engine messaging suite in C++ exploring **TCP/IP Sockets with Multithreading** and **POSIX Shared Memory with Semaphore Synchronization**.

---

## 📌 Project Overview
DualSync-IPC is designed to explore and compare two fundamental Inter-Process Communication (IPC) paradigms in Unix-like operating systems:

1. **System A (Networked - Multi-threaded Sockets):** 
   * Client-Server architecture over TCP/IP (`socket`, `bind`, `listen`, `accept`, `connect`).
   * Concurrent multi-client communication using Threads (`std::thread` / `pthreads`).
   * Supports communication across different machines over the network.

2. **System B (Local - Synchronized Shared Memory):** 
   * Ultra-fast zero-copy local messaging using POSIX/System V Shared Memory (`shmget` / `shmat`).
   * Process synchronization and race-condition prevention via Semaphores (`sem_wait`, `sem_post`).
   * Operates between independent processes on the same machine.

3. **User Interface (Simple GUI):**
   * A clean graphical interface connecting to both messaging engines.

---

## 🏗️ System Architecture & Workflow Diagram

The diagram below illustrates the end-to-end dataflow and concurrency model of **System A**:
- **Client Processes:** Independent Unix processes connecting over loopback TCP (`127.0.0.1:8080`).
- **Master Listener Thread:** Main server loop listening on port `8080`, continuously accepting new connections and assigning incremental client IDs.
- **Worker Thread Pool:** Each connected client is immediately offloaded to a detached background worker thread (`std::thread::detach`), ensuring non-blocking concurrent communication.

<p align="center">
  <img src="docs/diagrams/system_a_workflow.png" alt="DualSync System A Architecture and Workflow Diagram" width="100%" />
</p>

---

## 📸 Live Demonstrations

### System A: Multi-Threaded TCP Socket Chat (Terminal)
Real-time concurrent message exchange between multiple TCP clients (`Client 1`, `Client 2`) and the multi-threaded server running on `127.0.0.1:8080`:

<p align="center">
  <img src="docs/screenshots/socket_chat_demo.jpg" alt="DualSync System A Terminal Sockets Demo" width="95%" />
</p>

---

## 📂 Project Architecture
```text
DualSync-IPC/
├── system-a-sockets/       # Networked Chat Engine (Sockets + Threads)
├── system-b-shm/           # Local High-Speed Chat Engine (Shared Memory + Semaphores)
├── gui/                    # Simple Graphical Interface
└── docs/                   # Documentation, Diagrams, and Screenshots
    ├── diagrams/           # System Workflow & Architecture Diagrams
    └── screenshots/        # Verified Terminal & GUI Execution Logs
```

---

## 🎓 Academic Context
* **Institution:** Egyptian E-Learning University (EELU) - Faculty of Computers & IT
* **Course:** Operating Systems (Fall 2026–2027)
* **Supervised by:** Dr. Wafaa Samy & Eng. Dyaa Elden Yahya
* **Project Team:**
  1. Ahmed Harby Makawy (Team Leader - Core Architecture)
  2. Andro Emil Nasry
  3. Ahmed Ali Ahmed
  4. Ahmed Saber Ahmed
  5. Fatma Ahmed Mohamed
