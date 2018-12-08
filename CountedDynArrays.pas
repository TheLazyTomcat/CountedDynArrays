{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays - basic types and constants

  ©František Milt 2018-12-06

  Version 1.0

  Dependencies:
    AuxTypes - github.com/ncs-sniper/Lib.AuxTypes

===============================================================================}
{===============================================================================
--------------------------------------------------------------------------------
  For examples of how to implement a counted dynamic array, refer to files
  CountedDynArrays*.pas, where * is name of the base type.

  Arrays for following types are implemented in current version of this
  library and should be shipped with it:

    Boolean    in CountedDynArraysBoolean.pas
    Integer    in CountedDynArraysInteger.pas
    TDateTime  in CountedDynArraysDateTime.pas
    String     in CountedDynArraysString.pas
    Pointer    in CountedDynArraysPointer.pas
    TObject    in CountedDynArraysTObject.pas
    Int8       in CountedDynArraysInt8.pas
    UInt8      in CountedDynArraysUInt8.pas
    Int16      in CountedDynArraysInt16.pas
    UInt16     in CountedDynArraysUInt16.pas
    Int32      in CountedDynArraysInt32.pas
    UInt32     in CountedDynArraysUInt32.pas
    Int64      in CountedDynArraysInt64.pas
    UInt64     in CountedDynArraysUInt64.pas
    Float32    in CountedDynArraysFloat32.pas
    Float64    in CountedDynArraysFloat64.pas

  Note that given the method used (template with type alias), there is a limit
  of one array type per *.pas file.

  If you want to override any preimplemented method, define symbol
  CDA_DisableFunc_<FunctionName> and write your own implementation.
  Example how to do it can be found in unit CountedDynArraysString.pas.

--------------------------------------------------------------------------------
===============================================================================}
unit CountedDynArrays;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

type
{
  Array is only grown if current count + DeltaMin is larger than current capacity.

  agmSlow           - grow by 1
  agmLinear         - grow by GrowFactor (integer part of the float)
  agmFast           - grow by capacity * GrowFactor
  agmFastAttenuated - if capacity is below DYNARRAY_GROW_ATTENUATE_THRESHOLD,
                      then grow by capacity * GrowFactor
                    - if capacity is above or equal to DYNARRAY_GROW_ATTENUATE_THRESHOLD,
                      grow by 1/16 * DYNARRAY_GROW_ATTENUATE_THRESHOLD

  If mode is other than agmSlow and current capacity is 0, then new capacity is
  set to DYNARRAY_INITIAL_CAPACITY, irrespective of selected grow mode.
}
  TCDAGrowMode = (agmSlow, agmLinear, agmFast, agmFastAttenuated);

{
  asmKeepCap - array is not shrinked, capacity is preserved
  asmNormal  - if capacity is above DYNARRAY_INITIAL_CAPACITY and count is below capacity div 4,
               then capacity is set to capacity div 4, otherwise capacity is preserved
             - if capacity is below or equal to DYNARRAY_INITIAL_CAPACITY, then the array
               is not shinked unless the count is 0, in which case the new capacity is set to 0
  asmToCount - capacity is set to count
}
  TCDAShrinkMode = (asmKeepCap, asmNormal, asmToCount);

const
  DYNARRAY_INITIAL_CAPACITY         = 16;
  DYNARRAY_GROW_ATTENUATE_THRESHOLD = 16 * 1024 * 1024;

implementation

end.


