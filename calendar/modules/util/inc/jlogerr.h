/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil c-basic-offset: 2 -*- 
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

/* 
 * jlogerr.h
 * John Sun
 * 6/22/98 2:13:19 PM
 */
#ifndef __JULIANLOGERROR_H_
#define __JULIANLOGERROR_H_

#include "unistring.h"
#include "ptrarray.h"
#include "nscalutilexp.h"

/**
 *  Encapsulates a Log Error Message.  A log error message has more than just
 *  the error string.  It also has a priority level and an error log number id.
 *  TODO: c++doc this 
 */
class NS_CAL_UTIL nsCalLogError
{
private:
    /*-----------------------------
    ** MEMBERS
    **---------------------------*/
    /*UnicodeString m_ErrorString;*/
    t_int32 m_Priority;
    t_int32 m_ErrorID;

    UnicodeString m_ShortReturnStatusCode;
    UnicodeString m_OffendingData;
    /*-----------------------------
    ** PRIVATE METHODS
    **---------------------------*/
    nsCalLogError();
public:
    /*-----------------------------
    ** CONSTRUCTORS and DESTRUCTORS
    **---------------------------*/
#if 0
    nsCalLogError(UnicodeString & errorString, 
        t_int32 errorPriority);
#endif
    nsCalLogError(t_int32 errorID,
        UnicodeString & shortReturnStatusCode,
        UnicodeString & offendingData, t_int32 errorPriority);

    virtual ~nsCalLogError() {}
    /*----------------------------- 
    ** ACCESSORS (GET AND SET) 
    **---------------------------*/ 
    //UnicodeString getErrorString() const { return m_ErrorString; }
    t_int32 getPriority() const { return m_Priority; }
    /*t_int32 getID() const { return m_ID; }*/

    t_int32 getErrorID() const { return m_ErrorID; }
    UnicodeString getShortReturnStatusCode() const { return m_ShortReturnStatusCode; }
    UnicodeString getOffendingData() const { return m_OffendingData; }

    //void setErrorString(UnicodeString & errorString) { m_ErrorString = errorString; }
    //void setPriority(t_int32 i) { m_Priority = i; }
    /*void setID(t_int32 i) { m_ID = i; }*/
    /*----------------------------- 
    ** UTILITIES 
    **---------------------------*/
    //UnicodeString toString() { return m_ErrorString; }
    /*----------------------------- 
    ** STATIC METHODS 
    **---------------------------*/ 
    static void deleteNsCalLogErrorVector(JulianPtrArray * errors);
    /*----------------------------- 
    ** OVERLOADED OPERATORS 
    **---------------------------*/ 
};

#endif /* __JULIANLOGERROR_H_ */

