/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "It_vfs_jffs.h"

static UINT32 TestCase(VOID)
{
    INT32 ret;
    INT32 fd = -1;
    INT32 i = 0;
    CHAR pathname1[JFFS_STANDARD_NAME_LENGTH] = { JFFS_PATH_NAME0 };
    DIR *dir = NULL;
    DIR *dir1[JFFS_MIDDLE_ARRAY_LENGTH] = {NULL};

    ret = mkdir(pathname1, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT);

    dir = opendir(pathname1);
    ICUNIT_GOTO_NOT_EQUAL(dir, NULL, dir, EXIT1);

    while (i < JFFS_MIDDLE_ARRAY_LENGTH) {
        dir1[i] = opendir(pathname1);
        ICUNIT_GOTO_NOT_EQUAL(dir1[i], NULL, dir1[i], EXIT1);

        i++;
    }
    for (i = 0; i < JFFS_MIDDLE_ARRAY_LENGTH; i++) {
        ret = closedir(dir1[i]);
        ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT1);
    }
    ret = closedir(dir);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT1);

    ret = rmdir(pathname1);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT);

    ret = chdir("/");
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT2);

    ret = umount(JFFS_MAIN_DIR0);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT2);

    ret = mount(JFFS_DEV_PATH0, JFFS_MAIN_DIR0, JFFS_FILESYS_TYPE, 0, NULL);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT2);

    ret = chdir(JFFS_MAIN_DIR0);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT2);

    return JFFS_NO_ERROR;
EXIT2:
    mount(JFFS_DEV_PATH0, JFFS_MAIN_DIR0, JFFS_FILESYS_TYPE, 0, NULL);
    return JFFS_NO_ERROR;
EXIT1:
    closedir(dir);
EXIT:
    rmdir(pathname1);
    return JFFS_NO_ERROR;
}

VOID ItFsJffsPressure305(VOID)
{
    TEST_ADD_CASE("ItFsJffsPressure305", TestCase, TEST_VFS, TEST_JFFS, TEST_LEVEL3, TEST_PRESSURE);
}
