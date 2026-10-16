# Student + Library Management System

### First Team Project Plan — 3 Members, Semester 1, C Language

---

## 1. What Are You Building? (Keep It Small!)

Don't try to build a real college software. Build an **MVP (Minimum Viable Product)** first, then add extras if time is left.

### MVP Features (Must Have)

**Student Module:**

- [ ] Add a student (Roll No, Name, Branch, Semester)
- [ ] View all students
- [ ] Search student by Roll No
- [ ] Update student details
- [ ] Delete a student

**Library Module:**

- [ ] Add a book (Book ID, Title, Author, Copies)
- [ ] View all books
- [ ] Search book by ID / Title
- [ ] Issue a book to a student (check if student exists + book available)
- [ ] Return a book

**Common:**

- [ ] Main menu that connects both modules
- [ ] Save data to files so it doesn't disappear when program closes

### Stretch Features (Only If MVP Is Done)

- Fine calculation for late return
- Sort students by name / roll
- Low-stock book warning
- Admin login (simple password)
- View all currently issued books

> **Rule:** No one starts a stretch feature until the MVP works end-to-end.

---

## 2. How To Divide Work Among 3 People

This division is designed so you rarely edit the same file at the same time — that's the #1 cause of team fights.

| Person       | Role                   | Owns These Files               | Responsibilities                                                      |
| :----------- | :--------------------- | :----------------------------- | :-------------------------------------------------------------------- |
| **Person A** | Student Module Lead    | `student.c`, `student.h`       | All student CRUD: add, view, search, update, delete students          |
| **Person B** | Library Module Lead    | `library.c`, `library.h`       | All book CRUD + issue/return logic                                    |
| **Person C** | Integrator / Core Lead | `main.c`, `utils.c`, `utils.h` | Main menu, file handling helpers, connecting A + B, testing & merging |

**Why Person C's job is NOT the easy job:** C owns the glue. When A's and B's code needs to talk (e.g., "can this student issue a book?"), C makes it work. C is also the Git/merging in-charge.

**Rotate if you want:** If one person finishes early, they don't sit idle — they help with testing and documentation.

---

## 3. The Golden Rule: Decide The "Contract" Together FIRST

Before anyone writes real code, sit together for 1-2 hours and **all 3 of you together** decide these. Write them in header (`.h`) files and DON'T change them without telling everyone.

### a) The Structs (in a shared file `common.h`)

```c
typedef struct {
    int rollNo;
    char name[50];
    char branch[20];
    int semester;
} Student;

typedef struct {
    int bookId;
    char title[100];
    char author[50];
    int totalCopies;
    int availableCopies;
} Book;

typedef struct {
    int rollNo;      // which student
    int bookId;      // which book
    char issueDate[20];
} IssueRecord;
```

### b) The Function Signatures

```c
// student.h — Person A promises these will exist
void addStudent(void);
void viewStudents(void);
void searchStudent(void);
int  studentExists(int rollNo);   // Person B will NEED this for issuing!

// library.h — Person B promises these will exist
void addBook(void);
void viewBooks(void);
void issueBook(void);    // internally calls studentExists()
void returnBook(void);
```

### c) The Data Files

- `students.dat` — stores Student records
- `books.dat` — stores Book records
- `issued.dat` — stores IssueRecord records

Use binary files (`fopen(..., "ab")`, `fwrite`, `fread`) — simpler and cleaner than text for structs.

> **If you change a struct or a function name later, EVERYONE's code breaks. That's why you lock this on Day 1.**

---

## 4. Project File Structure

```
student-library-system/
│
├── main.c          <- Person C
├── common.h        <- All 3 decide together, nobody changes alone
├── student.h       <- Person A
├── student.c       <- Person A
├── library.h       <- Person B
├── library.c       <- Person B
├── utils.h         <- Person C (input helpers, clearing screen, etc.)
├── utils.c         <- Person C
├── README.md       <- All 3
└── .gitignore      <- ignore *.dat, *.exe / a.out
```

**Compile command (all of you use the same):**

```bash
gcc main.c student.c library.c utils.c -o app
./app        # on Windows: app.exe
```

---

## 5. How To Work Together: Git & GitHub (Learn This, It's Industry Skill)

Don't send code on WhatsApp / pen drives. That way lies chaos.

### One-Time Setup (Day 1)

1. One person creates a repo on GitHub: `student-library-system`
2. Adds the other 2 as collaborators (Settings → Collaborators)
3. Everyone clones it:

```bash
git clone <repo-link>
```

### Daily Workflow (Every Person, Every Day)

```bash
# 1. Before starting work, get latest code
git pull

# 2. Create YOUR branch (first time only)
git checkout -b feature/student-module     # A
git checkout -b feature/library-module     # B
git checkout -b feature/main-menu          # C

# 3. Work, then save your work
git add .
git commit -m "add: addStudent() function"

# 4. Push your branch
git push origin feature/student-module
```

### Rules That Will Save You

1. **NEVER push directly to `main`.** Always use your own branch, then merge.
2. **One person = one file.** A doesn't touch `library.c`, B doesn't touch `student.c`. Need a change in someone else's file? Ask them.
3. **Commit small and often.** "added addStudent" > one giant commit "did everything".
4. **Good commit messages:** `add:`, `fix:`, `update:` + what you did.
5. **Pull before you push.** Always.
6. **Person C reviews & merges** branches into `main` when a feature is working.

> Merge conflict? Don't panic and don't randomly delete code. Sit together (or call), look at both versions, decide what stays. It's normal — professionals get them daily.

### Communication

- Make a WhatsApp/Discord group ONLY for this project
- Daily 2-line update: _"Done: search student. Working on: delete. Stuck on: file reading"_
- Use GitHub Issues or a simple shared list (Notion / Google Doc / Trello) as a task board: To Do → Doing → Done

---

## 6. 14-Day Plan

| Days          | What Happens                                                                                                                                                 |
| :------------ | :----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Day 1**     | Team meeting. Lock structs, function names, file structure (Section 3). Create GitHub repo. Everyone gets the empty project compiling.                       |
| **Day 2**     | Person C: skeleton `main.c` with menu loop (options print, but call empty functions). All: header files written. **Goal: program compiles and menu shows.**  |
| **Day 3–6**   | Everyone builds their module on their own branch. A: student CRUD. B: book CRUD. C: file helpers, utils, input validation. Daily push + 15-min evening sync. |
| **Day 7**     | **First Integration Day.** Merge A's and B's branches. Connect issueBook() → studentExists(). Expect bugs. Fix together, same room if possible.              |
| **Day 8–10**  | Finish remaining features, return book flow, data saving/loading properly.                                                                                   |
| **Day 11–12** | Testing phase (see checklist below). Fix bugs. Edge cases: duplicate roll no, issuing a book with 0 copies, searching non-existent ID, empty file.           |
| **Day 13**    | README, comments cleanup, remove debug prints. Prepare viva answers.                                                                                         |
| **Day 14**    | Final demo practice. One person presents, but all 3 must be able to explain ANY part.                                                                        |

---

## 7. Testing Checklist (Test Each Other's Code!)

- [ ] Add student with duplicate roll number → should be rejected
- [ ] Search for a roll number that doesn't exist → proper message, no crash
- [ ] Issue book to non-existent student → rejected
- [ ] Issue book with 0 available copies → rejected
- [ ] Issue a book, check available copies decreased by 1
- [ ] Return the book, copies increased back
- [ ] Close program, reopen → data is still there
- [ ] Delete a student / view empty list → no crash, clean message
- [ ] Type letters where numbers are expected → program shouldn't break weirdly

**Rule:** The person who wrote the code is the WORST person to test it. Test each other's modules.

---

## 8. Coding Rules For The Whole Team

1. Same naming style: `camelCase` for functions (`addStudent`), structs start capital (`Student`)
2. Header guards in every `.h` file:
   ```c
   #ifndef STUDENT_H
   #define STUDENT_H
   // ...
   #endif
   ```
3. One function = one job. If a function is crossing ~50 lines, split it.
4. No copy-pasting each other's code without understanding it — viva will expose you.
5. Comment _why_, not _what_: `// check duplicate before inserting` ✅
6. No global variables unless all 3 agree. Pass data via parameters/returns.

---

## 9. Likely Viva Questions (All 3 Should Know)

1. Why did you use binary files instead of text files?
2. Why separate `.h` and `.c` files?
3. How does `fwrite`/`fread` work with structs?
4. How do you check if a student exists before issuing a book?
5. What happens to your data when the program closes? Why?
6. How did you divide work / use Git as a team?
7. What was the hardest bug you faced?

---

## 10. If You Get Stuck

1. Google the exact error / read the compiler error top-to-bottom
2. Try alone for 30 mins → then ask in your group chat with screenshot + what you tried
3. Still stuck after a day → ask senior / teacher / AI with your specific code

**Stuck is normal. Silent-and-stuck-for-3-days is the actual problem. Communicate early.**

---

### Remember

A finished small project > an unfinished big project.
Get the MVP working first. Polish later.

Good luck! 🚀
