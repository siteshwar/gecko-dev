/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- 
 * 
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape 
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */

// prprtyfy.cpp
// John Sun
// 5:19 PM February 12 1998

#include "stdafx.h"
#include "jdefines.h"

#include "prprtyfy.h"
#include "prprty.h"
#include "dprprty.h"
#include "duprprty.h"
#include "iprprty.h"
#include "sprprty.h"
//#include "bprprty.h"
//#include "pprprty.h"


ICalPropertyFactory::ICalPropertyFactory()
{
}

//---------------------------------------------------------------------

ICalProperty *
ICalPropertyFactory::Make(ICalProperty::PropertyTypes aType, void * value, 
                          JulianPtrArray * parameters)
{

    PR_ASSERT(value != 0);
    if (value != 0)
    {
        switch (aType)
        {
        case ICalProperty::TEXT:
            return new StringProperty(*((UnicodeString *) value), parameters);
        case ICalProperty::DATETIME:
            return new DateTimeProperty(*((DateTime *) value), parameters);
        case ICalProperty::INTEGER:
            return new IntegerProperty(*((t_int32 *) value), parameters);
        case ICalProperty::DURATION:
            return new DurationProperty(*((nsCalDuration *) value), parameters);
        case ICalProperty::PERIOD:
            return 0;
            //return new PeriodProperty((Period *) value, parameters);
        case ICalProperty::BOOLEAN:
            return 0;
            //return new BooleanProperty(*(t_bool *) value, parameters);
        default:
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------


