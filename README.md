# Belajar Low Level Game Development
## Playground 1 - Space Shooter Game

## Log Belajar

### 17/07/2026
- Konfigurasi sistem environment Windows 11 dari nol.
- Instal compiler C++, library SFML, dan CodeBlocks.
- Membuat program pertama untuk menampilkan window.
- Belajar menampilkan object SFML (shape dan text).
- Belajar input keyboard WASD untuk menggerakkan object shape.
- Menampilkan teks di belakang object.

### 17/07/2026 (lanjutan)
- Menambahkan asset gambar, musik, dan font.
- Mengganti object shape menjadi texture untuk menampilkan object ship.
- Menambahkan mekanisme menembakkan peluru dari object ship.
- Menambahkan struct dari beberapa komponen penting untuk mekanik menembak.
- Menambahkan beberapa input keyboard untuk rotasi dan menembak.

### 18/07/2026
- Memperbaiki bug musik.
- Memperbaiki logika projectile peluru.
- Memperbaiki error struct dari object.

### 19/07/2026
- Progress logika projectile peluru.
- Progress logika peluru.
- Progress penempatan peluru.
- IDEA:
  - Menambahkan logika penyimpanan peluru.
  - Menambahkan logika mag peluru.
  - Menambahkan object target tembak.
  - Menambahkan poin jika peluru mengenai target.

### 22/07/2026
- Progress logika penempatan peluru.
- Logika posisi peluru.
- Logika hitbox peluru.
- Logika hitbox target.

### 23/07/2026
- Fix fitur bullet.
- Menambahkan enemy.

### 03/08/2026
- Rebuild from scratch.
- Menyusun ulang proyek dengan mengimplementasikan arsitektur yang lebih rapi.

## Struktur Direktori

```text
SpaceShooter/
├── assets/
│   ├── fonts/
│   ├── music/
│   ├── sounds/
│   └── textures/
├── include/
│   └── Engine/
│       └── Engine.hpp
├── src/
│   ├── Engine/
│   │   └── Engine.cpp
│   └── main.cpp
└── CMakeLists.txt (atau file project Code::Blocks)
```

## Diagram Arsitektur Kelas

```text
+-------------------------------------------------------+
|                       Engine                          |
+-------------------------------------------------------+
| - m_window       : sf::RenderWindow                   |
| - m_timePerFrame : const sf::Time (1/60s)             |
| - m_isRunning    : bool                               |
+-------------------------------------------------------+
| + Engine()                                            |
| + run()          : void                               |
| - processEvents(): void                               |
| - update(sf::Time fixedTime) : void                   |
| - render()       : void                               |
+-------------------------------------------------------+
```

