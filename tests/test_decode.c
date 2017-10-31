/**
 *  Copyright 2017 Comcast Cable Communications Management, LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <CUnit/Basic.h>

#include "../src/schedule.h"
#include "../src/decode.h"

uint8_t decode_buffer[] = {
0x83, 0xA6, 0x77, 0x65, 0x65, 0x6B, 0x6C, 0x79, 0x93, 0x82, 0xA4, 0x74,
0x69, 0x6D, 0x65, 0x0A, 0xA7, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x65, 0x73,
0x93, 0x00, 0x01, 0x03, 0x82, 0xA4, 0x74, 0x69, 0x6D, 0x65, 0x14, 0xA7,
0x69, 0x6E, 0x64, 0x65, 0x78, 0x65, 0x73, 0x91, 0x00, 0x82, 0xA4, 0x74,
0x69, 0x6D, 0x65, 0x1E, 0xA7, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x65, 0x73,
0xC0, 0xA4, 0x6D, 0x61, 0x63, 0x73, 0x94, 0xB1, 0x31, 0x31, 0x3A, 0x32,
0x32, 0x3A, 0x33, 0x33, 0x3A, 0x34, 0x34, 0x3A, 0x35, 0x35, 0x3A, 0x61,
0x61, 0xB1, 0x32, 0x32, 0x3A, 0x33, 0x33, 0x3A, 0x34, 0x34, 0x3A, 0x35,
0x35, 0x3A, 0x36, 0x36, 0x3A, 0x62, 0x62, 0xB1, 0x33, 0x33, 0x3A, 0x34,
0x34, 0x3A, 0x35, 0x35, 0x3A, 0x36, 0x36, 0x3A, 0x37, 0x37, 0x3A, 0x63,
0x63, 0xB1, 0x34, 0x34, 0x3A, 0x35, 0x35, 0x3A, 0x36, 0x36, 0x3A, 0x37,
0x37, 0x3A, 0x38, 0x38, 0x3A, 0x64, 0x64, 0xA8, 0x61, 0x62, 0x73, 0x6F,
0x6C, 0x75, 0x74, 0x65, 0x91, 0x82, 0xA9, 0x75, 0x6E, 0x69, 0x78, 0x2D,
0x74, 0x69, 0x6D, 0x65, 0xCE, 0x59, 0xE5, 0x83, 0x17, 0xA7, 0x69, 0x6E,
0x64, 0x65, 0x78, 0x65, 0x73, 0x92, 0x00, 0x02
};

size_t decode_length = sizeof(decode_buffer);

uint8_t decode_buffer2[] = {
131, 166, 119, 101, 101, 107, 108, 121, 148, 130, 164, 116, 105, 109, 101, 10,
167, 105, 110, 100, 101, 120, 101, 115, 148, 0, 1, 5, 3, 130, 164, 116, 105,
109, 101, 20, 167, 105, 110, 100, 101, 120, 101, 115, 145, 0, 130, 164, 116,
105, 109, 101, 30, 167, 105, 110, 100, 101, 120, 101, 115, 147, 1, 5, 2, 130,
164, 116, 105, 109, 101, 205, 1, 45, 167, 105, 110, 100, 101, 120, 101, 115,
147, 0, 3, 7, 164, 109, 97, 99, 115, 152, 177, 49, 49, 58, 50, 50, 58, 51, 51,
58, 52, 52, 58, 53, 53, 58, 97, 97, 177, 50, 50, 58, 51, 51, 58, 52, 52, 58,
53, 53, 58, 54, 54, 58, 98, 98, 177, 51, 51, 58, 52, 52, 58, 53, 53, 58, 54,
54, 58, 55, 55, 58, 99, 99, 177, 52, 52, 58, 53, 53, 58, 54, 54, 58, 55, 55,
58, 56, 56, 58, 100, 100, 177, 49, 49, 58, 50, 50, 58, 51, 51, 58, 52, 52, 58,
53, 53, 58, 97, 48, 177, 50, 50, 58, 51, 51, 58, 52, 52, 58, 53, 53, 58, 54,
54, 58, 98, 48, 177, 51, 51, 58, 52, 52, 58, 53, 53, 58, 54, 54, 58, 55, 55,
58, 99, 48, 177, 52, 52, 58, 53, 53, 58, 54, 54, 58, 55, 55, 58, 56, 56, 58,
100, 57, 168, 97, 98, 115, 111, 108, 117, 116, 101, 145, 130, 169, 117, 110,
105, 120, 45, 116, 105, 109, 101, 206, 89, 229, 131, 23, 167, 105, 110, 100,
101, 120, 101, 115, 146, 0, 2
};
size_t decode_length2 = sizeof(decode_buffer2);

uint8_t decode_buffer_corrupted [] = {
131, 185, 119, 101, 101, 107, 108, 121, 45, 115, 99, 104, 101, 100, 117, 108,
101, 148, 130, 164, 116, 105, 109, 101, 10, 167, 105, 110, 100, 101, 120, 101,
115, 148, 0, 1, 5, 3, 130, 164, 116, 105, 109, 101, 20, 167, 105, 110, 100, 101,
120, 101, 115, 145, 0, 130, 164, 116, 105, 109, 101, 30, 167, 105, 110, 100, 101,
120, 101, 115, 147, 1, 5, 2, 130, 164, 116, 105, 109, 101, 205, 1, 45, 167, 105,
110, 100, 101, 120, 101, 115, 147, 0, 3, 7, 164, 109, 97, 99, 115, 152, 177, 49,
49, 58, 50, 50, 58, 51, 51, 58, 52, 52, 58, 53, 53, 58, 97, 97, 177, 50, 50, 58,
51, 51, 58, 52, 52, 58, 53, 53, 58, 54, 54, 58, 98, 98, 177, 51, 51, 58, 52, 52,
58, 53, 53, 58, 54, 54, 58, 55, 55, 58, 99, 99, 177, 52, 52, 58, 53, 53, 58, 54,
54, 58, 55, 55, 58, 56, 56, 58, 100, 100, 177, 49, 49, 58, 50, 50, 58, 51, 51,
58, 52, 52, 58, 53, 53, 58, 97, 48, 177, 50, 50, 58, 51, 51, 58, 52, 52, 58, 53,
53, 58, 54, 54, 58, 98, 48, 177, 51, 51, 58, 52, 52, 58, 53, 53, 58, 54, 54, 58,
55, 55, 58, 99, 48, 177, 52, 52, 58, 53, 53, 58, 54, 54, 58, 55, 55, 58, 56, 56,
58, 100, 57, 177, 97, 98, 115, 111, 108, 117, 116, 101, 45, 115, 99, 104, 101,
100, 117, 108, 101, 145, 130, 169, 117, 110, 105, 120, 45, 116, 105, 109, 101,
206, 89, 229, 131, 23, 167, 105, 110, 100, 101, 120, 101, 115, 146, 0, 2
};
size_t buffer_corrupt_length = sizeof(decode_buffer_corrupted);

/* Invalid msgpack */
uint8_t decode_buffer_3[] = {
0x00, 0xAF, 0x77, 0x65,   0x65, 0x6B, 0x6C, 0x79,   0x2D, 0x73, 0x63, 0x68,
0x65, 0x64, 0x75, 0x6C,   0x65, 0x93, 0x82, 0xA4,   0x74, 0x69, 0x6D, 0x65,
0x0A, 0xA7, 0x69, 0x6E,   0x64, 0x65, 0x78, 0x65,   0x73, 0x93, 0x00, 0x01,
0x03, 0x82, 0xA4, 0x74,   0x69, 0x6D, 0x65, 0x14,   0xA7, 0x69, 0x6E, 0x64,
0x65, 0x78, 0x65, 0x73,   0x91, 0x00, 0x82, 0xA4,   0x74, 0x69, 0x6D, 0x65,
0x1E, 0xA7, 0x69, 0x6E,   0x64, 0x65, 0x78, 0x65,   0x73, 0x90, 0xA4, 0x6D,
0x61, 0x63, 0x73, 0x94,   0xB1, 0x31, 0x31, 0x3A,   0x32, 0x32, 0x3A, 0x33,
0x33, 0x3A, 0x34, 0x34,   0x3A, 0x35, 0x35, 0x3A,   0x61, 0x61, 0xB1, 0x32,
0x32, 0x3A, 0x33, 0x33,   0x3A, 0x34, 0x34, 0x3A,   0x35, 0x35, 0x3A, 0x36,
0x36, 0x3A, 0x62, 0x62,   0xB1, 0x33, 0x33, 0x3A,   0x34, 0x34, 0x3A, 0x35,
0x35, 0x3A, 0x36, 0x36,   0x3A, 0x37, 0x37, 0x3A,   0x63, 0x63, 0xB1, 0x34,
0x34, 0x3A, 0x35, 0x35,   0x3A, 0x36, 0x36, 0x3A,   0x37, 0x37, 0x3A, 0x38,
0x38, 0x3A, 0x64, 0x64,   0xB1, 0x61, 0x62, 0x73,   0x6F, 0x6C, 0x75, 0x74,
0x65, 0x2D, 0x73, 0x63,   0x68, 0x65, 0x64, 0x75,   0x6C, 0x65, 0x91, 0x82,
0xA9, 0x75, 0x6E, 0x69,   0x78, 0x2D, 0x74, 0x69,   0x6D, 0x65, 0xCE, 0x59,
0xE5, 0x83, 0x17, 0xA7,   0x69, 0x6E, 0x64, 0x65,   0x78, 0x65, 0x73, 0x92,
0x00, 0x02
};
size_t decode_length_3 = sizeof(decode_buffer_3);


void decode_test()
{
    schedule_t *t;
    int ret = decode_schedule(decode_length, decode_buffer, &t);
    CU_ASSERT(0 == ret);
    destroy_schedule(t);
    ret = decode_schedule(decode_length2, decode_buffer2, &t);
    CU_ASSERT(0 == ret);
    destroy_schedule(t);
    t = NULL;
    ret = decode_schedule(buffer_corrupt_length, decode_buffer_corrupted, &t);
    CU_ASSERT(0 != ret);
    ret = decode_schedule(decode_length_3, decode_buffer_3, &t);
    CU_ASSERT(0 != ret);
    ret = decode_schedule(0, decode_buffer, &t);
    CU_ASSERT(0 != ret);
}

void add_suites( CU_pSuite *suite )
{
    printf("--------Start of Test Cases Execution ---------\n");
    *suite = CU_add_suite( "tests", NULL, NULL );
    CU_add_test( *suite, "Decode Test", decode_test);
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();

    }

    return rv;
}
