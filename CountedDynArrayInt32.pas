{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of Int32 values

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayInt32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TInt32CountedDynArray = record
    Arr:    array of Int32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PInt32CountedDynArray = ^TInt32CountedDynArray;

  TCDABaseType = Int32;
  PCDABaseType = PInt32;

  TCDAArrayType = TInt32CountedDynArray;
  PCDAArrayType = PInt32CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Int32): Integer;
begin
Result := Integer(B - A);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
