# Versioning System Overview

The versioning system of this software follows the **PENIX** software development standard. Below is a brief explanation of its structure. Please note that this standard may change entirely in the future, and if that happens, this file will be updated accordingly.

---

## PENIX Versioning Structure

The versioning system defined by PENIX consists of the following components:

ver-<Major version>.<Minor version>.<Status>


### 1. **Major Version**
The **Major version** is incremented when significant changes are made to the software's structure and behavior, resulting in incompatibility with previous versions. These changes may affect input, output, or other parts of the software.

### 2. **Minor Version**
The **Minor version** is updated for changes that do not affect the core structure of the software or introduce incompatibility with previous versions.

### 3. **Status**
The **Status** section is represented by Latin letters, which indicate the current stage of the software:

- **`b`**: This indicates the software is in a **Beta** state—unstable, untested, and not suitable for official use. However, if you want to stay up to date with the latest changes, you can use it.

- **`a`**: This indicates the **Official**, stable, and usable version of the software.

- **`b+`**: This indicates an unstable **Beta** version with complete documentation. This version includes full and detailed documentation.

- **`a+`**: This indicates the stable, **Official** version of the software with complete documentation.

---

## Example Versions:

- `ver-1.0-b`: A beta version of release `1.0`, unstable and untested.
- `ver-1.0-a`: The official and stable release of version `1.0`.
- `ver-1.0-b+`: An unstable beta version with complete documentation.
- `ver-1.0-a+`: A stable official version with complete documentation.

---

This system ensures clear differentiation between development stages and makes it easier for users to understand the software's current state.

