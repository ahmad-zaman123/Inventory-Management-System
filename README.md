  # Inventory Management System

  A console-based inventory tracker in C++ for managing items and lending them out
  to people (e.g. faculty members). Inventory and allocation records persist to
  text files, so data survives between runs.

  ## Features

  A 9-option menu:

  1. **Add** an item (rejects duplicates)
  2. **View** all items
  3. **Search** for an item and see who currently has it
  4. **Edit** item details
  5. **Delete** an item
  6. **Assign** an item to a person (decrements available count)
  7. **Retrieve** a returned item (restores count)
  8. **View borrowers** — everyone holding an assigned item
  9. **Exit**

  - Case-insensitive search
  - Formatted tabular output (`setw`)
  - Input validation for empty/missing data

  ## Data storage

  Plain text files, loaded into memory on startup and written back on change:

  - `inventory_item_data.txt` — item records
  - `allocated_item_data.txt` — assignment records

  ## Build & run

  ```bash
  g++ "Inventory Management System.cpp" -o inventory
  ./inventory
  ```
  
  ## Tech

  C++ standard library only (structs for InventoryItem and person,
  file I/O via fstream). No external dependencies.

  ---
