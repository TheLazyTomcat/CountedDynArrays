Function Length(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function Capacity(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function FreeCapacity(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function Count(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}

Function Low(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function High(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function CheckIndex(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer): Boolean; overload;{$IFDEF CanInline} inline; {$ENDIF}

procedure Init(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}); overload;
procedure SetLength(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; NewLength: Integer); overload;
procedure SetCapacity(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; NewCapacity: Integer); overload;{$IFDEF CanInline} inline; {$ENDIF}
procedure Clear(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}); overload;{$IFDEF CanInline} inline; {$ENDIF}

Function Grow(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; GrowMode: TArrayGrowMode = agmFast; GrowFactor: Single = 2.0; DeltaMin: Integer = 1): Integer; overload;
procedure Shrink(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; ShrinkMode: TArrayShrinkMode = asmNormal); overload;

procedure UniqueArray(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}); overload;{$IFDEF CanInline} inline; {$ENDIF}
procedure Copy(const Src: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; out Dst: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}); overload;
Function Copy(const Src: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; overload;{$IFDEF CanInline} inline; {$ENDIF}

Function GetItem(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer): {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_BaseTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_BaseType.Inc'}{$ENDIF}; overload;
procedure SetItem(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer; {$IFDEF CDA_TypeString}const {$ENDIF}Item: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_BaseTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_BaseType.Inc'}{$ENDIF}); overload;
