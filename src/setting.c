/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2015 Ivan Alonso (Kaian)
 ** Copyright (C) 2015 Irontec SL. All rights reserved.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
/**
 * @file setting.c
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Source code of functions defined in setting.h
 *
 */
#include "config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "setting.h"


//! Available configurable settings
setting_t settings[SETTING_COUNT] =
{
  { SETTING_BACKGROUND,         "background",       SETTING_FMT_ENUM,    "dark",    SETTING_ENUM_BACKGROUND },
  { SETTING_COLORMODE,          "colormode",        SETTING_FMT_ENUM,    "request", SETTING_ENUM_COLORMODE },
  { SETTING_SYNTAX,             "syntax",           SETTING_FMT_ENUM,    "on",      SETTING_ENUM_ONOFF },
  { SETTING_SYNTAX_TAG,         "syntax.tag",       SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_SYNTAX_BRANCH,      "syntax.branch",    SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_ALTKEY_HINT,        "hintkeyalt",       SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_CAPTURE_LIMIT,      "capture.limit",    SETTING_FMT_NUMBER,  "50000",   NULL },
  { SETTING_CAPTURE_LOOKUP,     "capture.lookup",   SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_CAPTURE_DEVICE,     "capture.device",   SETTING_FMT_STRING,  "any",     NULL },
  { SETTING_CAPTURE_INFILE,     "capture.infile",   SETTING_FMT_STRING,  NULL,      NULL },
  { SETTING_CAPTURE_OUTFILE,    "capture.outfile",  SETTING_FMT_STRING,  NULL,      NULL },
  { SETTING_CAPTURE_KEYFILE,    "capture.keyfile",  SETTING_FMT_STRING,  NULL,      NULL },
  { SETTING_SIP_NOINCOMPLETE,   "sip.noincomplee",  SETTING_FMT_ENUM,    "on",      SETTING_ENUM_ONOFF },
  { SETTING_SIP_CALLS,          "sip.calls",        SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_SAVEPATH,           "savepath",         SETTING_FMT_STRING,  NULL,      NULL },
  { SETTING_DISPLAY_HOST,       "displayhost",      SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_DISPLAY_ALIAS,      "displayalias",     SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_CL_FILTER,          "cl.filter",        SETTING_FMT_STRING,  NULL,      NULL },
  { SETTING_CL_EXITPROMPT,      "cl.exitprompt",    SETTING_FMT_ENUM,    "on",      SETTING_ENUM_ONOFF },
  { SETTING_CL_SCROLLSTEP,      "cl.scrollstep",    SETTING_FMT_NUMBER,  "4",       NULL },
  { SETTING_CF_FORCERAW,        "cf.forceraw",      SETTING_FMT_ENUM,    "on",      SETTING_ENUM_ONOFF },
  { SETTING_CF_RAWMINWIDTH,     "cf.rawminwidth",   SETTING_FMT_NUMBER,  "40",      NULL },
  { SETTING_CF_RAWFIXEDWIDTH,   "cf.rawfixedwidth", SETTING_FMT_NUMBER,  NULL,      NULL },
  { SETTING_CF_SPLITCALLID,     "cf.splitcallid",   SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_CF_HIGHTLIGHT,      "cf.highlight",     SETTING_FMT_ENUM,    "bold",    SETTING_ENUM_HIGHLIGHT },
  { SETTING_CF_SCROLLSTEP,      "cf.scrollstep",    SETTING_FMT_NUMBER,  "4",       NULL },
  { SETTING_CF_LOCALHIGHLIGHT,  "cf.localhighlight", SETTING_FMT_ENUM,   "on",      SETTING_ENUM_ONOFF },
  { SETTING_CF_SDP_ONLY,        "cf.sdponly",       SETTING_FMT_ENUM,    "off",     SETTING_ENUM_ONOFF },
  { SETTING_CR_SCROLLSTEP,      "cr.scrollstep",    SETTING_FMT_NUMBER,  "10",      NULL },
  { SETTING_FILTER_METHODS,     "filter.methods",   SETTING_FMT_STRING,  NULL,      NULL },
};

setting_t *
setting_by_id(enum setting_id id)
{
    int i;
    for (i = 0; i < SETTING_COUNT; i++) {
        if (id == settings[i].id)
            return &settings[i];
    }
    return NULL;
}

setting_t *
setting_by_name(const char *name)
{
    int i;
    for (i = 0; i < SETTING_COUNT; i++) {
        if (!strcmp(name, settings[i].name))
            return &settings[i];
    }
    return NULL;
}

enum setting_id
setting_id(const char *name)
{
    const setting_t *sett = setting_by_name(name);
    return (sett) ? sett->id : -1;
}

const char *
setting_name(enum setting_id id)
{
    const setting_t *sett = setting_by_id(id);
    return (sett) ? sett->name : NULL;
}

enum setting_fmt
setting_format(enum setting_id id)
{
    const setting_t *sett = setting_by_id(id);
    return (sett) ? sett->fmt : -1;
}

const char *
setting_get_value(enum setting_id id)
{
    const setting_t *sett = setting_by_id(id);
    return (sett) ? sett->value : NULL;
}

int
setting_get_intvalue(enum setting_id id)
{
    const setting_t *sett = setting_by_id(id);
    return (sett && sett->value) ? atoi(sett->value) : -1;
}

void
setting_set_value(enum setting_id id, const char *value)
{
    setting_t *sett = setting_by_id(id);
    if (sett) {
        sett->value = (value) ? strdup(value) : NULL;
    }
}

void
setting_set_intvalue(enum setting_id id, int value)
{
    char strvalue[80];
    sprintf(strvalue, "%d", value);
    setting_set_value(id, strvalue);
}

int
setting_enabled(enum setting_id id)
{

    return setting_has_value(id, "on") ||
            setting_has_value(id, "yes");
}

int
setting_has_value(enum setting_id id, const char *value)
{
    setting_t *sett = setting_by_id(id);
    if (sett && sett->value) {
        return !strcmp(sett->value, value);
    }

    return 0;
}

void
setting_toggle(enum setting_id id)
{
    const char *value;
    setting_t *sett = setting_by_id(id);

    if (sett) {
        if (sett->fmt == SETTING_FMT_STRING)
            return;
        if (sett->fmt == SETTING_FMT_NUMBER)
            return;
        if (sett->fmt == SETTING_FMT_ENUM) {
            if ( (value = setting_enum_next(id, setting_get_value(id)) )) {
                setting_set_value(id, value);
            } else {
                setting_set_value(id, setting_enum_next(id, NULL));
            }
        }
    }
}

const char *
setting_enum_next(enum setting_id id, const char *value)
{
    char vvalues[256];
    static char *vvalue, *vnext;
    setting_t *sett;

    if (!(sett = setting_by_id(id)))
        return NULL;

    strncpy(vvalues, sett->vvalues, sizeof(vvalues));
    vvalue = strtok(vvalues, ", ");

    // If setting has no value, set the first one
    if (!value)
        return vvalue;

    // Iterate through valid values
    while(vvalue) {
        vnext = strtok(NULL, ", ");
        // If current value matches
        if (!strcmp(vvalue, value)) {
            return vnext;
        }
        vvalue = vnext;
    }

    return NULL;
}

const char *
setting_enum_prev(enum setting_id id, const char *value)
{
    char vvalues[256];
    static char *vvalue, *vnext;
    setting_t *sett;

    if (!(sett = setting_by_id(id)))
        return NULL;

    strncpy(vvalues, sett->vvalues, sizeof(vvalues));
    vvalue = strtok(vvalues, ", ");

    // If setting has no value, set the first one
    if (!value)
        return vvalue;

    // Iterate through valid values
    while(vvalue) {
        vnext = strtok(NULL, ", ");
        // If current value matches
        if (vnext && !strcmp(vnext, value)) {
            return vvalue;
        }
        vvalue = vnext;
    }

    return NULL;
}
