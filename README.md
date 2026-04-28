# POS Switch Simulator (C++)

## 📌 Overview

This project simulates a **Payment Switch System** similar to real-world networks like Visa/Mastercard. It processes ISO8583 transactions with routing, fraud detection, and issuer simulation.

---

## 🧱 Architecture

* TCP Gateway (handles POS connections)
* ISO8583 Parser (bitmap + LLVAR support)
* Switch Core (transaction orchestration)
* Router (BIN-based routing)
* Fraud Engine (rule-based detection)
* Issuer Simulator (approve/decline logic)
* Thread Pool (efficient concurrency)

---

## 🚀 Features

* Multi-threaded request handling using thread pool
* ISO8583 message parsing (MTI + bitmap + fields)
* Pluggable fraud detection engine
* Modular and extensible design
* POS client simulator for testing

---

## 🛠️ Tech Stack

* C++17
* STL (threads, mutex, condition_variable)
* POSIX sockets
* CMake build system

---

## ▶️ How to Build & Run

### 1. Clone Project

```
git clone <your-repo-url>
cd pos-switch
```

### 2. Create Build Directory

```
mkdir build
cd build
```

### 3. Run CMake

```
cmake ..
```

### 4. Compile

```
make
```

---

## ▶️ Run the Server

```
./pos_switch
```

---

## ▶️ Run POS Client (New Terminal)

```
./pos_client
```

---

## 📊 Sample Flow

1. POS sends ISO8583 request
2. Switch parses message
3. Fraud checks applied
4. Routed to issuer
5. Response returned

---

## 🚧 Future Enhancements

* Async networking (Boost.Asio)
* Real ISO8583 spec support
* Kafka integration
* Load testing (10K TPS)
* Monitoring dashboard

---

## 💡 Learning Outcome

This project demonstrates:

* Low-latency system design
* Multithreading & concurrency
* Financial domain knowledge
* Clean modular architecture

---
