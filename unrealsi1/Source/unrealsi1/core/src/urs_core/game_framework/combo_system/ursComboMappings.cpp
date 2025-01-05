#include "ursComboMappings.h"

#if 0
#pragma mark --- FursComboMappings-Decl ---
#endif // 0
#if 1

const UursComboSet* 
FursComboMappings::findComboSet(const TArray<FursComboKey>& keys)
{
	// TODO: revise combo mapping update, use hash to find solve lots of problem
	// however, need to find out solution for two button pressed at the same time
	
	//const UursComboSet* ret = nullptr;

	if (keys.Num() == 0)
		return nullptr;

	for (const auto& e : _comboSets)
	{
		auto srcCount = keys.Num();
		auto dstCount = e->comboKeys.Num();

		if (srcCount != dstCount)
			continue;

		bool isSame = true;
		for (size_t i = 0; i < dstCount; i++)
		{
			auto& srcKey = keys[i];
			auto& dstKey = e->comboKeys[i];

			isSame = srcKey.inputAction == dstKey.inputAction && srcKey.value.GetMagnitudeSq() == dstKey.value.GetMagnitudeSq();
			if (!isSame)
				break;
		}
		return e;
	}

	return nullptr;
}

FursFnComboExecute*
FursComboMappings::findComboCallback(const UursComboSet* set)
{
	return _comboCallbackTable.Find(set);
}

void 
FursComboMappings::executeComboSet(const UursComboSet* set)
{
	auto* fn = findComboCallback(set);
	if (fn)
	{
		fn->ExecuteIfBound(set);
	}
}


#endif
