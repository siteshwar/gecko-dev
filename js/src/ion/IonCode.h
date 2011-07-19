/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=79:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   David Anderson <danderson@mozilla.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef jsion_coderef_h__
#define jsion_coderef_h__

#include "jscell.h"

namespace JSC {
    class ExecutablePool;
}

namespace js {
namespace ion {

class IonCode : public gc::Cell
{
    uint8 *code_;
    uint32 size_;
    JSC::ExecutablePool *pool_;
    uint32 padding_;

    IonCode()
      : code_(NULL),
        pool_(NULL)
    { }
    IonCode(uint8 *code, uint32 size, JSC::ExecutablePool *pool)
      : code_(code),
        size_(size),
        pool_(pool)
    { }

  public:
    uint8 *code() const {
        return code_;
    }
    uint32 size() const {
        return size_;
    }
    void finalize(JSContext *cx);

    // Allocates a new IonCode object which will be managed by the GC. If no
    // object can be allocated, NULL is returned. On failure, |pool| is
    // automatically released, so the code may be freed.
    static IonCode *New(JSContext *cx, uint8 *code, uint32 size, JSC::ExecutablePool *pool);
};

#define ION_DISABLED_SCRIPT ((IonScript *)0x1)

// An IonScript attaches Ion-generated information to a JSScript.
struct IonScript
{
    IonCode *method;

  private:
    void trace(JSTracer *trc, JSScript *script);

  public:
    static void Trace(JSTracer *trc, JSScript *script);
    static void Destroy(JSContext *cx, JSScript *script);
};

}
}

#endif // jsion_coderef_h__

