/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
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

#ifndef nsCalProperty_h___
#define nsCalProperty_h___

#include "nsICalProperty.h"
#include "nsICalICalendarParserObject.h"

#include "sdprprty.h"

class NS_CAL_CORE_ICAL nsCalProperty : public nsICalProperty,
                                       public nsICalICalendarParserObject
{
public:
  nsCalProperty();
  ~nsCalProperty();

public:

  NS_DECL_ISUPPORTS

  NS_IMETHOD Init();

  /* nsICalICalendarParserObject */
  NS_IMETHOD SetParameter(nsString & aKey, nsString & aValue) = 0;

  /* nsICalStandardProperty */
  NS_IMETHOD_(JulianPtrArray *) GetParameters() = 0;
  NS_IMETHOD SetParameters(JulianPtrArray * parameters) = 0;

  NS_IMETHOD_(ICalProperty *) GetICalProperty() const;

protected:
  ICalProperty * mICalProperty;

};
#endif

