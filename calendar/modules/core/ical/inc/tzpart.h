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

/* 
 * tzpart.h
 * John Sun
 * 2/24/98 9:48:53 AM
 */

#ifndef __TZPART_H_
#define __TZPART_H_

#include <unistring.h>
#include "icalcomp.h"
#include "datetime.h"

/**
 * Implements the standardc and daylightc parts of an iCal VTimeZone object.
 */
class TZPart: public ICalComponent
{
private:
#if 0
    /** 
     * Default constructor.  Hide from clients.
     */
    TZPart();
#endif 
protected:
    /** 
     * Copy constructor.
     * @param           that    TZPart to copy
     */
    TZPart(TZPart & that);

public:

    /**
     * Create TZPart, passing in a logfile.
     * @param           initLog     log file to write errors to
     */
    TZPart(JLog * initLog = 0);

    /**
     * Destructor
     */
    ~TZPart();

    /*  -- Start of ICALComponent interface -- */

    /**
     * The parse method is the standard interface for ICalComponent
     * subclasses to parse from an ICalReader object 
     * and from the ITIP method type (i.e. PUBLISH, REQUEST, CANCEL, etc.).
     * The method type can be set to \"\" if there is no method to be loaded.
     * Also accepts a vector of VTimeZone objects to apply to
     * the DateTime properties of the component.
     * 4-2-98:  Added bIgnoreBeginError.  If desired to start parsing in Component level,
     * it is useful to ignore first "BEGIN:".   Setting bIgnoreBeginError to TRUE allows for
     * this.
     *     
     * @param   brFile              ICalReader to load from
     * @param   sType               name of component (i.e. VEVENT, VTODO, VTIMEZONE)
     * @param   parseStatus         return parse error status string (normally return "OK")
     * @param   vTimeZones          vector of VTimeZones to apply to datetimes
     * @param   bIgnoreBeginError   TRUE = ignore first "BEGIN:DAYLIGHT(STANDARD)", FALSE otherwise
     * @param   encoding            the encoding of the stream,  default is 7bit.
     *
     * @return  parse error status string (parseStatus)
     */
    virtual UnicodeString & parse(ICalReader * brFile, UnicodeString & sType, 
        UnicodeString & parseStatus, JulianPtrArray * vTimeZones = 0,
        t_bool bIgnoreBeginError = FALSE,
        nsCalUtility::MimeEncoding encoding = nsCalUtility::MimeEncoding_7bit);
    
    /**
     * Returns a clone of this object
     * @param           initLog     log file to write errors to
     *
     * @return          clone of this object
     */
    virtual ICalComponent * clone(JLog * initLog);

    /**
     * Return TRUE if component is valid, FALSE otherwise
     *
     * @return          TRUE if is valid, FALSE otherwise
     */
    virtual t_bool isValid();
    
    /**
     * Print all contents of ICalComponent to iCal export format.
     *
     * @return          string containing iCal export format of ICalComponent
     */
    virtual UnicodeString toICALString();

    /**
     * Print all contents of ICalComponent to iCal export format, depending
     * on attendee name, attendee delegated-to, and where to include recurrence-id or not
     *
     * @param           method          method name (REQUEST,PUBLISH, etc.)
     * @param           name            attendee name to filter with
     * @param           isRecurring     TRUE = no recurrenceid, FALSE = include recurrenceid
     *
     * @return          string containing iCal export format of ICalComponent
     */
    virtual UnicodeString toICALString(UnicodeString method, UnicodeString name,
        t_bool isRecurring);

    /**
     * Print all contents of ICalComponent to human-readable string.
     *
     * @return          string containing human-readable format of ICalComponent
     */
    virtual UnicodeString toString();

    /**
     * Depending on character passed in, returns a string that represents
     * the ICAL export string of that property that the character represents, if 
     * other paramaters not null, then print out information is filtered in several ways
     * Attendee print out can be filtered so that only attendee with certain name is printed
     * also, can print out the relevant attendees in a delegation message
     * (ie. owner, delegate-to, delegate-from) 
     *
     * @param       c                   char of what property to print
     * @param       sFilterAttendee     name of attendee to print
     * @param       bDelegateRequest    TRUE if a delegate request, FALSE if not
     * @return                          ICAL export format of that property
     */
    virtual UnicodeString formatChar(t_int32 c, UnicodeString sFilterAttendee,
        t_bool delegateRequest = FALSE);

    /**
     * convert a character to the content of a property in string 
     * human-readable format
     * @param           c           a character represents a property
     * @param           dateFmt     for formatting datetimes
     *
     * @return          property in human-readable string
     */
    virtual UnicodeString toStringChar(t_int32 c, UnicodeString & dateFmt);

    /**
     * Returns the ICAL_COMPONENT enumeration value of this ICalComponent.
     * Each ICalComponent subclass must return a unique ICAL_COMPONENT value.
     *
     * @return          ICAL_COMPONENT value of this component
     */
    virtual ICAL_COMPONENT GetType() const { return ICAL_COMPONENT_TZPART; }

    /**
     * Update the private property data-members with updatedComponent's 
     * property data-members.
     * Usually, overwriting data-members should only occur if updatedComponent
     * is more recent than the current component.
     * Return TRUE if component was changed, FALSE otherwise
     * @param           ICalComponent * updatedComponent
     *
     * @return          virtual t_bool 
     */
    virtual t_bool updateComponent(ICalComponent * updatedComponent);

    /*  -- End of ICALComponent interface -- */

    /* COMMENT */
    void addComment(UnicodeString s, JulianPtrArray * parameters = 0);
    void addCommentProperty(ICalProperty * prop);
    JulianPtrArray * getComment() const              { return m_CommentVctr; }

    /* TZNAME */
    void addTZName(UnicodeString s, JulianPtrArray * parameters = 0);
    void addTZNameProperty(ICalProperty * prop);
    JulianPtrArray * getTZName() const              { return m_TZNameVctr; }

    /* DTSTART */
    DateTime getDTStart() const;
    void setDTStart(DateTime s, JulianPtrArray * parameters = 0);
    ICalProperty * getDTStartProperty() const { return m_DTStart; }

    /* RDATE */
    DateTime getRDate() const;
    void setRDate(DateTime s, JulianPtrArray * parameters = 0);
    ICalProperty * getRDateProperty() const { return m_RDate; }

    /* RRULE */
    UnicodeString getRRule() const;
    void setRRule(UnicodeString s, JulianPtrArray * parameters = 0);
    ICalProperty * getRRuleProperty() const { return m_RRule; }
    
    /* TZOFFSETTO */
    UnicodeString getTZOffsetTo() const;
    void setTZOffsetTo(UnicodeString s, JulianPtrArray * parameters = 0);
    ICalProperty * getTZOffsetToProperty() const { return m_TZOffsetTo; }

    /* TZOFFSETFROM */
    UnicodeString getTZOffsetFrom() const;
    void setTZOffsetFrom(UnicodeString s, JulianPtrArray * parameters = 0);
    ICalProperty * getTZOffsetFromProperty() const { return m_TZOffsetFrom; }

    /* XTOKENS: NOTE: a vector of strings, not a vector of ICalProperties */
    void addXTokens(UnicodeString s);
    JulianPtrArray * getXTokens() const { return m_XTokensVctr; }

    /* NAME (DAYLIGHT OR STANDARD) */
    UnicodeString getName() const { return m_Name; }
    void setName(UnicodeString s);

    /**
     * Return start month value of timezone part start time. 0-based
     *
     * @return          start month value (0-11)
     */
    t_int32 getMonth() const { return m_StartMonth; }
    
    /**
     * Return start day of week in month value of timezone part start time.
     * Usually -1 or 1.
     * @return          start day of week in month (-5 to 5)
     */
    t_int32 getDayOfWeekInMonth() const { return m_StartWeek; }

    /**
     * Return start day of timezone part start time.
     * Usually Calendar::SUNDAY
     * @return          start day value (Calendar::SUNDAY - Calendar::SATURDAY)
     * @see Calendar
     */
    t_int32 getDay() const { return m_StartDay; }

    /**
     * Return starting time in milliseconds of timezone part start time.
     * For example, if start time is 2AM, then return 7200000.
     *
     * @return          start time value in milliseconds
     */
    t_int32 getStartTime() const { return m_StartTime; }

    /**
     * Return expiration date of TimeZone part, if returned value is
     * invalid, then no expiration date.
     *
     * @return          expiration date, invalid means no expiration date
     */
    DateTime getUntil() { return m_Until; }

    /* TODO: move later */
    static float UTCOffsetToFloat(UnicodeString & utcOffset);

private:

    /**
     * Helper method called by updateComponent to actually replace
     * the property data-members with updatedComponent's data-members.
     * @param           TZPart * updatedComponent
     *
     * @return          virtual void 
     */
    void updateComponentHelper(TZPart * updatedComponent);

    /**
     * Selfcheck data members.  Currently does nothing
     */
    void selfCheck();
    
    /**
     * store the data, depending on property name, property value
     * parameter names, parameter values, and the current line
     *
     * @param       strLine         current line to process
     * @param       propName        name of property
     * @param       propVal         value of property
     * @param       parameters      property's parameters
     * @param       vTimeZones      vector of timezones
     */
    void storeData(UnicodeString & strLine, UnicodeString & propName,
        UnicodeString & propVal, JulianPtrArray * parameters);
public:

    typedef void (TZPart::*SetOp) (UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);

    /* Clients should NOT call below methods */
    void storeComment(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeTZName(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeDTStart(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeRDate(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeRRule(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeTZOffsetTo(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    void storeTZOffsetFrom(UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones);
    
    void ApplyStoreOp(void (TZPart::*op) (UnicodeString & strLine, 
        UnicodeString & propVal, JulianPtrArray * parameters, JulianPtrArray * vTimeZones), 
        UnicodeString & strLine, UnicodeString & propVal, 
        JulianPtrArray * parameters, JulianPtrArray * vTimeZones)
    {
        (this->*op)(strLine, propVal, parameters, vTimeZones);
    }

private:

    /**
     * Takes RRULE value and generates startmonth, startday, startweek, starttime
     * and until.  Return TRUE if parse went OK, FALSE if error occurred.
     *
     * @return          TRUE if parse went OK, FALSE if error occurred.
     */
    t_bool parseRRule();

    /**
     * Takes RDATE value and generates startmonth, startday, startweek.
     */
    void parseRDate();

#if 0
    /**
     * Given data members, generates timezone critical information
     * (start month,day,week,time,until).  Calls either parseRRule or
     * parseRDate to do this.  If error in parse, return FALSE, else
     * return TRUE.
     *
     * @return          TRUE if parse went OK, FALSE if error occurred 
     */
    t_bool parseRule();
#endif


    /* -- DATA MEMBERS -- */

    /*static UnicodeString m_strDefaultFmt;
    static UnicodeString ms_sAllMessage;*/

    /* for RRULE timezones */
    t_int32 m_StartMonth;
    t_int32 m_StartDay;
    t_int32 m_StartWeek;
    t_int32 m_StartTime;

    /* used to print out DTStart back */
    t_int32 m_iStartYear;
    t_int32 m_iStartMonth;
    t_int32 m_iStartDay;
    t_int32 m_iStartHour;
    t_int32 m_iStartMinute;
    t_int32 m_iStartSecond;

    /* used to print out RDate back */
    t_int32 m_iRDateYear;
    t_int32 m_iRDateMonth;
    t_int32 m_iRDateDay;
    t_int32 m_iRDateHour;
    t_int32 m_iRDateMinute;
    t_int32 m_iRDateSecond;

    DateTime m_Until;

    UnicodeString m_Name; /* STANDARD or DAYLIGHT */

    JulianPtrArray * m_CommentVctr;
    JulianPtrArray * m_TZNameVctr;
    ICalProperty * m_DTStart;
    ICalProperty * m_RDate;
    ICalProperty * m_RRule;
    ICalProperty * m_TZOffsetTo;
    ICalProperty * m_TZOffsetFrom;
    JulianPtrArray * m_XTokensVctr;      /* TEXT */

    JLog * m_Log;
};

#endif /* __TZPART_H_ */
