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
#ifndef nsICalendarContainer_h___
#define nsICalendarContainer_h___

#include "nsIWebViewerContainer.h"
#include "nsIWidget.h"
#include "nsIStreamListener.h"
#include "nsICalendarShell.h"
#include "nsICalendarWidget.h"
#include "nsIMenuManager.h"

//9a221a70-3077-11d2-9247-00805f8a7ab6
#define NS_ICALENDAR_CONTAINER_IID   \
{ 0x9a221a70, 0x3070, 0x11d2,    \
{ 0x92, 0x47, 0x00, 0x80, 0x5f, 0x8a, 0x7a, 0xb6 } }

class nsICalendarContainer : public nsIWebViewerContainer 
{

public:
  NS_IMETHOD Init(nsIWidget * aParent,
                  const nsRect& aBounds,
                  nsICalendarShell * aCalendarShell) = 0;
  NS_IMETHOD_(nsEventStatus) HandleEvent(nsGUIEvent *aEvent) = 0;

  NS_IMETHOD_(nsICalendarWidget *) GetDocumentWidget() = 0;


};


#endif /* nsICalendarContainer */
