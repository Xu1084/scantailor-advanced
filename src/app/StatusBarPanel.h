
#ifndef SCANTAILOR_STATUSBARPANEL_H
#define SCANTAILOR_STATUSBARPANEL_H

#include <QtCore/QMutex>
#include <QtWidgets/QWidget>
#include "Dpi.h"
#include "ImageViewInfoListener.h"
#include "ImageViewInfoProvider.h"
#include "UnitsListener.h"
#include "ui_StatusBarPanel.h"

class PageId;

class StatusBarPanel : public QWidget, public UnitsListener, public ImageViewInfoListener {
  Q_OBJECT
 public:
  StatusBarPanel();

  ~StatusBarPanel() override = default;

 public:
  void onMousePosChanged(const QPointF& mousePos) override;

  void onPhysSizeChanged(const QSizeF& physSize) override;

  void onDpiChanged(const Dpi& dpi) override;

  void onProviderStopped() override;

  void updatePage(int pageNumber, size_t pageCount, const PageId& pageId);

  void clear();

  void onUnitsChanged(Units) override;

 private:
  void mousePosChanged();

  void physSizeChanged();

  Ui::StatusBarPanel ui;
  QPointF m_mousePos;
  QSizeF m_physSize;
  Dpi m_dpi;
};


#endif  // SCANTAILOR_STATUSBARPANEL_H