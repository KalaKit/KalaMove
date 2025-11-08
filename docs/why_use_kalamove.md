# Why `.kmf` over scripting?  

| Advantage                  | Explanation |
|----------------------------|-------------|
| **Strict & Repeatable**    | Every `.kmf` file follows the same format with strict rules. No surprises, no “works on my machine” problems - execution is always consistent. |
| **Cross-Platform by Design** | A single `.kmf` manifest works on both **Windows** and **Linux**, thanks to the OS-agnostic `@` separator. |
| **Readable & Maintainable** | `.kmf` files are plain text with human-friendly keys like `origin`, `target`, and `action`. No need to debug fragile scripts. |
| **Multiple Targets**       | A single `origin` can copy to multiple `target` locations in one block — something most batch/shell/CMake setups handle poorly. |
| **Safe by Default**        | Invalid origins immediately stop execution, preventing data loss. Invalid targets are skipped safely without halting everything. |

# Why `.kmf` over installers?  

Traditional installers (NSIS, Inno Setup, MSI, etc.) are often **overkill** if you only need basic file operations like moving, copying, renaming or deleting files or just creating directories. They come with:  
- OS lock-in (Windows-only).  
- Complex scripting languages.  
- Extra features (registry, compression, uninstallers) you may not need.  

**KalaMove** provides a simpler alternative:  

| Feature                    | KalaMove |
|----------------------------|----------|
| **Cross-platform**         | Yes - `.kmf` works on both Windows & Linux |
| **Executable size**        | < 1 MB standalone `.exe` |
| **Transparency**           | Users can read `.kmf` files directly |
| **Zero setup**             | Drop KalaMove and the manifest file anywhere and run it |
| **Focused scope**          | Basic file operations only - no bloat |

# Real-World Use Cases  

- **Game Engine Development**  
  Keep shared headers, shaders, or assets synced between frameworks (`KalaWindow`) and dependent projects (`Elypso Engine`, `Elypso Hub`, `CircuitChan`).  

- **Multi-Repository Workflows**  
  Maintain 5–10 repositories that rely on the same master library. One `.kmf` ensures everything is copied consistently.  

- **End-User Distribution**  
  Instead of creating a full installer, ship your software with a `.kmf` manifest. The user runs `KalaMove.exe`, and files are placed correctly - repeatable, always the same.  

- **CI/CD Pipelines**  
  Use `.kmf` in automated build systems to copy outputs into test directories or package folders with strict validation.  