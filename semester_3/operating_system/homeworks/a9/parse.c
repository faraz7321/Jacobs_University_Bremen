#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "quiz.h"
#include <json-c/json.h>

struct json_object *find_something(struct json_object *jobj, const char *key)
{
    struct json_object *tmp;
    json_bool flag;
    flag = json_object_object_get_ex(jobj, key, &tmp);

    if (flag)
    {
        return tmp;
    }
    else
    {
        perror("json_object_object_get_ex");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief parses the JSON input and adds the next question
 *  and the expected answer to the quiz data structure
 *
 * @param json
 * @param quiz
 * @return int
 */
int parse(char *json, quiz_t *quiz)
{
    json_object *jobj, *temp;

    // parsing string into json object
    jobj = json_tokener_parse(json);

    // get question
    temp = find_something(jobj, "text");
    quiz->text = (char *)json_object_get_string(temp);

    // get answer
    temp = find_something(jobj, "number");
    quiz->number = (int)json_object_get_int(temp);

    // printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));

    return 1;
}