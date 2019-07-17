/*
Copyright 2016, Blur Studio

This file is part of Simplex.

Simplex is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Simplex is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Simplex.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "simplex.h"
#include "slider.h"

#include "rapidjson/document.h"

#include <vector>
#include <string>

using namespace simplex;

bool Slider::parseJSONv1(const rapidjson::Value &val, size_t index, Simplex *simp){
	if (!val[0u].IsString()) return false;
	if (!val[1].IsInt()) return false;

	std::string name(val[0u].GetString()); // needs to be 0u
	size_t slidx = size_t(val[1].GetInt());

	if (slidx >= simp->progs.size()) return false;
	simp->sliders.push_back(Slider(name, &simp->progs[slidx], index));
	return true;
}

bool Slider::parseJSONv2(const rapidjson::Value &val, size_t index, Simplex *simp){
	if (!val.IsObject()) return false;

	auto nameIt = val.FindMember("name");
	if (nameIt == val.MemberEnd()) return false;
	if (!nameIt->value.IsString()) return false;

	auto progIt = val.FindMember("prog");
	if (progIt == val.MemberEnd()) return false;
	if (!progIt->value.IsInt()) return false;

	std::string name(nameIt->value.GetString());
	size_t slidx = size_t(progIt->value.GetInt());
	
	if (slidx >= simp->progs.size()) return false;

	bool enabled = true;
	auto enIt = val.FindMember("enabled");
	if (enIt != val.MemberEnd()){
	    if (enIt->value.IsBool()){
			enabled = enIt->value.GetBool();
	    }
	}

	simp->sliders.push_back(Slider(name, &simp->progs[slidx], index));
	simp->sliders.back().setEnabled(enabled);
	return true;
}


