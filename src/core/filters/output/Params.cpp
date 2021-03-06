// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#include "Params.h"

#include <XmlMarshaller.h>
#include <XmlUnmarshaller.h>
#include <foundation/Utils.h>

using namespace foundation;

namespace output {
Params::Params() : m_dpi(600, 600), m_despeckleLevel(1.0), m_blackOnWhite(true) {}

Params::Params(const Dpi& dpi,
               const ColorParams& colorParams,
               const SplittingOptions& splittingOptions,
               const PictureShapeOptions& pictureShapeOptions,
               const dewarping::DistortionModel& distortionModel,
               const DepthPerception& depthPerception,
               const DewarpingOptions& dewarpingOptions,
               const double despeckleLevel)
    : m_dpi(dpi),
      m_colorParams(colorParams),
      m_splittingOptions(splittingOptions),
      m_pictureShapeOptions(pictureShapeOptions),
      m_distortionModel(distortionModel),
      m_depthPerception(depthPerception),
      m_dewarpingOptions(dewarpingOptions),
      m_despeckleLevel(despeckleLevel),
      m_blackOnWhite(true) {}

Params::Params(const QDomElement& el)
    : m_dpi(el.namedItem("dpi").toElement()),
      m_colorParams(el.namedItem("color-params").toElement()),
      m_splittingOptions(el.namedItem("splitting").toElement()),
      m_pictureShapeOptions(el.namedItem("picture-shape-options").toElement()),
      m_distortionModel(el.namedItem("distortion-model").toElement()),
      m_depthPerception(el.attribute("depthPerception")),
      m_dewarpingOptions(el.namedItem("dewarping-options").toElement()),
      m_despeckleLevel(el.attribute("despeckleLevel").toDouble()),
      m_blackOnWhite(el.attribute("blackOnWhite") == "1") {}

QDomElement Params::toXml(QDomDocument& doc, const QString& name) const {
  XmlMarshaller marshaller(doc);

  QDomElement el(doc.createElement(name));
  el.appendChild(m_distortionModel.toXml(doc, "distortion-model"));
  el.appendChild(m_pictureShapeOptions.toXml(doc, "picture-shape-options"));
  el.setAttribute("depthPerception", m_depthPerception.toString());
  el.appendChild(m_dewarpingOptions.toXml(doc, "dewarping-options"));
  el.setAttribute("despeckleLevel", Utils::doubleToString(m_despeckleLevel));
  el.appendChild(m_dpi.toXml(doc, "dpi"));
  el.appendChild(m_colorParams.toXml(doc, "color-params"));
  el.appendChild(m_splittingOptions.toXml(doc, "splitting"));
  el.setAttribute("blackOnWhite", m_blackOnWhite ? "1" : "0");
  return el;
}
}  // namespace output