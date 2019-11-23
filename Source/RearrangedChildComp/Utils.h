// Copyright 2019 Marc O. Rüdel. All Rights Reserved.
#pragma once



FString BytesToStringFixed(const uint8 *In, int32 Count)
{
	FString Broken = BytesToString(In, Count);
	FString Fixed;

	for (int i = 0; i < Broken.Len(); i++)
	{
		const TCHAR c = Broken[i] - 1;
		Fixed.AppendChar(c);
	}

	return Fixed;
}

FString ArrayOfUObjectToString(const TArray<USceneComponent*>* InArray, const FString separator = ", ")
{
	FString result = "";

	for (USceneComponent* item : *InArray) {
		result += item->GetFullName() + separator;
	}

	if (InArray->Num() > 0) {
		result = result.Mid(0, result.Len() - separator.Len());
	}
	return result;
}
