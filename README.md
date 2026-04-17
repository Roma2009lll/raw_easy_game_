# 🧙 RPG System (C++ OOP Project)

A console-based RPG system implemented in modern C++ demonstrating Object-Oriented Programming, memory management, and game logic architecture.

## 🚀 Features

- 🧩 Full OOP architecture (Inheritance, Polymorphism, Abstraction)
- ⚔️ Character system: Warrior, Mage, Rogue
- 🎒 Inventory system with smart pointers (`std::unique_ptr`)
- 🛡️ Equipment system (Weapons & Armor)
- 📜 Quest system:
  - Kill quests
  - Collect quests
- 👥 Party system (team management)
- 🧠 Smart pointers usage:
  - `std::unique_ptr`
  - `std::shared_ptr`
  - `std::weak_ptr`
- ⚠️ Custom exception handling

## 🏗️ Architecture

### Core Components

- **Character System**
  - Base abstract class `Character`
  - Derived classes: `Warrior`, `Mage`, `Rogue`
  - Polymorphic behavior (`calculateDamage`, `useAbility`)

- **Item System**
  - Abstract class `Item`
  - Derived: `Weapon`, `Armor`

- **Inventory**
  - Uses `std::vector<std::unique_ptr<Item>>`
  - Ownership-safe design (RAII)

- **Quest System**
  - Base class `Quest`
  - Derived:
    - `KillQuest`
    - `CollectQuest`
  - Uses `std::weak_ptr` to avoid cyclic dependencies

- **Party System**
  - `std::unordered_map<std::string, std::shared_ptr<Character>>`
  - Supports adding/removing members
  - Sorting by level

## 💡 Key Concepts Demonstrated

- Object-Oriented Design (SOLID basics)
- Memory Management with Smart Pointers
- RAII принцип
- Polymorphism & Dynamic Dispatch
- STL Containers (`vector`, `unordered_map`)
- Exception Handling
- Basic Game Logic Design

## 🧪 Example Functionality

- Create characters with different stats
- Equip weapons and armor
- Manage inventory
- Complete quests (kill / collect)
- Group characters into parties
- Sort players by level

