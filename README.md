# worldcupdb
Congratulations on accepting your new position as lead developer and database admin for the 2211 World Cup. As the resident C expert, you have been assigned the task of designing and implementing a database of all teams (nations) which will be used throughout the World Cup.

## Purpose
This assignment will ask you to apply the following concepts from class:

### Basic programming concepts
- Strings
- Structures
- Variable scope
## Design
To accomplish this task, each team will be stored as a structure with the following attributes:

Team code (eg. 0, 1, 2, 3, 4, etc.)

Each team code must be unique. Only integers 0-31 are acceptable

Team name (eg. "Australia", "Cameroon", "Canada", "Argentina", "Belgium", etc.)

Only team names up to 25 characters in length are acceptable (including the null character - So think of this as 24+1). Each team name must be unique

Group seeding (eg. "A1", "B3", "F2", etc.)

Only groups A-H and seeds 1-4 are acceptable. (So only A1, A2, A3, A4, B1, B2, ..., H3, H4). Each group seeding must be unique

Primary kit (uniform) colours (eg. "Red", "Orange", "Yellow", "Green", "Blue", "Indigo", and "Violet")

Only the values 'R', 'O', 'Y', 'G', 'B', 'I', 'V' are acceptable.

Your program will then use an array of structures to represent up to 32 possible teams.
