/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "BRNameMatchingPolicy.h"

#include "mozilla/Assertions.h"

using namespace mozilla::psm;
using namespace mozilla::pkix;

Result
BRNameMatchingPolicy::FallBackToCommonName(
  Time notBefore,
  /*out*/ FallBackToSearchWithinSubject& fallBackToCommonName)
{

  static const Time AUGUST_23_2016 = TimeFromEpochInSeconds(1471910400);
  switch (mMode)
  {
    case Mode::Enforce:
      fallBackToCommonName = FallBackToSearchWithinSubject::No;
      break;
    case Mode::EnforceAfter23August2015:
      fallBackToCommonName = notBefore > AUGUST_23_2015
                           ? FallBackToSearchWithinSubject::No
                           : FallBackToSearchWithinSubject::Yes;
      break;
    case Mode::EnforceAfter23August2016:
      fallBackToCommonName = notBefore > AUGUST_23_2016
                           ? FallBackToSearchWithinSubject::No
                           : FallBackToSearchWithinSubject::Yes;
      break;
    case Mode::DoNotEnforce:
      fallBackToCommonName = FallBackToSearchWithinSubject::Yes;
      break;
    default:
      MOZ_CRASH("Unexpected Mode");
  }
  return Success;
}
