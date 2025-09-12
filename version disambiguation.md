# Versioning System Overview

The versioning system of this software follows the **PENIX** software development standard. Below is a brief explanation of its structure. Please note that this standard may change entirely in the future, and if that happens, this file will be updated accordingly.

---

## PENIX Versioning Structure

The versioning system defined by PENIX consists of the following components:

ver-<Major version>.<Minor version>.<path>.<Status>


### 1. **Major Version**
Major Version refers to a version in which a significant and fundamental change has occurred in the software's structure and foundation, such that it is either incompatible with previous versions or has undergone major changes.

## 2. **Minor Version**
Minor Version refers to the addition of a new feature or the removal of a specific feature.

## 3. **Path**
Patch refers to small optimizations and changes that do not affect the usage compared to the previous version.

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

