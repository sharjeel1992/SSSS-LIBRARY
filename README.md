# 📚 SHHH Library Management System

Welcome to the **Stocking Hardy Harmonious Hardcopies (SHHH)** Library System — a fully object-oriented C++ project developed for CSS 343. This application simulates a library that manages publications, clients, and check-out/return operations using inheritance, custom data structures, and command processing from files.

---

## 🚀 Features

- 📘 Supports three publication types:
  - **Fiction** (sorted by author, then title)
  - **Children’s Books** (sorted by title, then author)
  - **Periodicals** (sorted by year, then month, then title)
- 🔁 Handles:
  - Checkout and return of items
  - Display of full library inventory
  - Viewing a client's complete borrowing history
- ✅ Implements:
  - **Custom hash table** for client management
  - **Binary search trees** for sorted publication storage
  - **Command pattern** to process checkout/return/display/history requests
- 📂 Designed for **easy extensibility** (new formats, commands, media types)

---

## 🧠 Design & Architecture

This project strictly adheres to object-oriented programming (OOP) principles:

- 🧬 **Inheritance** for media and command types
- 🧱 **Composition** for managing collections (containers, client-manager)
- 🔄 **Polymorphism** for uniform command execution
- 📦 **Encapsulation** of data and logic in well-defined classes

Refer to `assign4-design.pdf` for:
- UML diagrams
- Memory structure visualizations
- Pseudocode for key use cases
- Class hierarchy and relationships

---

## 📁 Folder Structure
|-> Client Side/ # Client, client hash table, and manager
|-> Command Side/ # Command classes: checkout, return, display, history
|-> Interface/ # Main program, library driver, and sample data files
|-> Publication Side/ # Media types (Fiction, Children, Periodicals) and structures
| -> README.md # This file
