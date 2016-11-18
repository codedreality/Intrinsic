// Copyright 2016 Benjamin Glatzel
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Precompiled header file
#include "stdafx_editor.h"
#include "stdafx.h"

// Ui
#include "ui_IntrinsicEdPropertyEditorVec4.h"

IntrinsicEdPropertyEditorVec4::IntrinsicEdPropertyEditorVec4(
    rapidjson::Document* p_Document, rapidjson::Value* p_CurrentProperties,
    rapidjson::Value* p_CurrentProperty, const char* p_PropertyName,
    QWidget* parent)
    : QWidget(parent), _property(p_CurrentProperty),
      _propertyName(p_PropertyName), _properties(p_CurrentProperties),
      _document(p_Document)
{
  _ui.setupUi(this);
  updateFromProperty();

  QObject::connect(_ui.x, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
  QObject::connect(_ui.y, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
  QObject::connect(_ui.z, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
  QObject::connect(_ui.w, SIGNAL(valueChanged(double)), this,
                   SLOT(onValueChanged()));
}

IntrinsicEdPropertyEditorVec4::~IntrinsicEdPropertyEditorVec4() {}

void IntrinsicEdPropertyEditorVec4::updateFromProperty()
{
  _INTR_ASSERT(_property);
  const rapidjson::Value& prop = *_property;

  if (prop["readOnly"].GetBool())
  {
    _ui.x->setReadOnly(true);
    _ui.y->setReadOnly(true);
    _ui.z->setReadOnly(true);
    _ui.w->setReadOnly(true);
  }

  _ui.x->setValue(prop["valueX"].GetFloat());
  _ui.y->setValue(prop["valueY"].GetFloat());
  _ui.z->setValue(prop["valueZ"].GetFloat());
  _ui.w->setValue(prop["valueW"].GetFloat());

  _ui.propertyTitle->setText(_propertyName.c_str());
}

void IntrinsicEdPropertyEditorVec4::onValueChanged()
{
  _INTR_ASSERT(_property);
  rapidjson::Value& prop = *_property;

  prop["valueX"].SetFloat((float)_ui.x->value());
  prop["valueY"].SetFloat((float)_ui.y->value());
  prop["valueZ"].SetFloat((float)_ui.z->value());
  prop["valueW"].SetFloat((float)_ui.w->value());

  emit valueChanged(*_properties);
}
