#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_STUDENTS 20

typedef struct {
  uint8_t grade;
  char name[MAX_NAME_LENGTH];
} student_t;

typedef struct {
  size_t count;
  student_t students[MAX_STUDENTS];
} roster_t;

void init_roster(roster_t *r) {
  r->count = 0;
  memset(r->students, 0, sizeof(r->students));
}

int student_exist(roster_t *r, const char *name) {
  for (size_t i = 0; i < r->count; i++) {
    if (strcmp(r->students[i].name, name) == 0) {
      return (int)i;
    }
  }

  return -1;
}

student_t create_student(const char *name, uint8_t grade) {
  student_t new_student;
  new_student.grade = grade;
  strcpy(new_student.name, name);
  return new_student;
}

roster_t get_grade(roster_t *roster, uint8_t grade) {
  roster_t r;
  init_roster(&r);

  for (size_t i = 0; i < roster->count; i++) {
    student_t s = roster->students[i];
    if (s.grade == grade) {
      r.students[r.count] = s;
      r.count++;
    }
  }

  return r;
}

int add_student(roster_t *actual, const char *name, uint8_t grade) {
  if (actual->count >= MAX_STUDENTS)
    return 0;

  int student_index = student_exist(actual, name);

  if (student_index != -1)
    return 0;

  int idx = -1;

  for (size_t i = 0; i < actual->count; i++) {
    student_t s = actual->students[i];

    if (s.grade >= grade) {
      idx = i;
      break;
    }
  }

  if (idx == -1) {
    actual->students[actual->count] = create_student(name, grade);
    actual->count++;

    return 1;
  }

  uint8_t aux_grade = grade;

  int i = idx;
  while (grade == aux_grade) {
    student_t s = actual->students[i];
    aux_grade = s.grade;

    if (aux_grade != grade || (int)s.name[0] > (int)name[0]) {
      idx = i;
      break;
    }
    i++;
  }

  roster_t aux;
  init_roster(&aux);

  for (size_t i = idx; i < actual->count; i++) {
    aux.students[i - idx] = actual->students[i];
    aux.count++;
  }
  actual->students[idx] = create_student(name, grade);
  for (size_t i = 0; i < aux.count; i++) {
    actual->students[idx + i + 1] = aux.students[i];
  }
  actual->count++;

  return 1;
}

static void check_roster_names(roster_t expected, roster_t actual) {

  for (size_t i = 0; i < expected.count; ++i)
    printf("%s == %s\n", expected.students[i].name, actual.students[i].name);
}

void test_students_are_sorted_by_name_in_grade(void) {
  uint8_t desired_grade = 5;
  roster_t expected = {2,
                       {(student_t){5, "Bradley"}, (student_t){5, "Franklin"}}};

  roster_t roster;
  init_roster(&roster);
  add_student(&roster, "Franklin", 5);
  add_student(&roster, "Bradley", 5);
  add_student(&roster, "Jeff", 1);
  roster_t actual = get_grade(&roster, desired_grade);

  printf("COUNT GRADE %d: %zu\n", desired_grade, actual.count);
  printf("----------------------------------------------\n");
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------\n");
}

void test_multiple_students_in_same_grade_are_added_to_roster(void) {
  printf("test_multiple_students_in_same_grade_are_added_to_roster\n");
  roster_t expected = {3,
                       {(student_t){2, "Blair"}, (student_t){2, "James"},
                        (student_t){2, "Paul"}}};
  roster_t actual;
  init_roster(&actual);
  add_student(&actual, "Blair", 2);
  add_student(&actual, "James", 2);
  add_student(&actual, "Paul", 2);
  ;

  check_roster_names(expected, actual);
  printf("----------------------------------------------\n");
  printf("%zu\n", actual.count);
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------\n");
}

static void check_rosters(roster_t expected, roster_t actual) {

  printf("%zu == %zu\n", expected.count, actual.count);

  check_roster_names(expected, actual);
}

void test_student_not_added_to_same_grade_in_roster_more_than_once(void) {
  printf("test_student_not_added_to_same_grade_in_roster_more_than_once\n");

  roster_t expected = {3,
                       {(student_t){2, "Blair"}, (student_t){2, "James"},
                        (student_t){2, "Paul"}}};

  roster_t actual;
  init_roster(&actual);
  add_student(&actual, "Blair", 2);
  add_student(&actual, "James", 2);
  add_student(&actual, "James", 2);
  add_student(&actual, "Paul", 2);
  check_rosters(expected, actual);
}

int main(int argc, char *argv[]) {
  roster_t actual;

  init_roster(&actual);

  printf("---------------------------------------------- \n");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Blair", 2)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "James", 2)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_FALSE\n", (add_student(&actual, "James", 3)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Paul", 2)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Bnna", 1)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Cnna", 1)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Dnna", 1)));

  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Ccna", 3)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------");
  printf("%d: TEST_ASSERT_TRUE\n", (add_student(&actual, "Acna", 1)));
  for (size_t i = 0; i < actual.count; i++) {
    student_t s = actual.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------\n");

  int grade = 2;
  roster_t r_grade = get_grade(&actual, (uint8_t)grade);
  printf("COUNT GRADE %d: %zu\n", grade, r_grade.count);
  printf("----------------------------------------------\n");
  for (size_t i = 0; i < r_grade.count; i++) {
    student_t s = r_grade.students[i];
    printf("Name: %s, Grade:%d\n", s.name, s.grade);
  }
  printf("----------------------------------------------\n");
  test_multiple_students_in_same_grade_are_added_to_roster();
  test_student_not_added_to_same_grade_in_roster_more_than_once();
  test_students_are_sorted_by_name_in_grade();
  return EXIT_SUCCESS;
}
