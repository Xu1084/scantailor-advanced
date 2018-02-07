/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PAGE_LAYOUT_FILTER_H_
#define PAGE_LAYOUT_FILTER_H_

#include "NonCopyable.h"
#include "AbstractFilter.h"
#include "PageView.h"
#include "intrusive_ptr.h"
#include "FilterResult.h"
#include "SafeDeletingQObjectPtr.h"
#include "PageOrderOption.h"
#include <QCoreApplication>
#include <vector>

class PageId;
class ProjectPages;
class PageSelectionAccessor;
class ImageTransformation;
class QString;
class QRectF;

namespace output {
    class Task;
    class CacheDrivenTask;
}

namespace page_layout {
    class OptionsWidget;
    class Task;
    class CacheDrivenTask;
    class Settings;

    class Filter : public AbstractFilter {
    DECLARE_NON_COPYABLE(Filter)

    Q_DECLARE_TR_FUNCTIONS(page_layout::Filter)
    public:
        Filter(intrusive_ptr<ProjectPages> page_sequence, const PageSelectionAccessor& page_selection_accessor);

        ~Filter() override;

        QString getName() const override;

        PageView getView() const override;

        void selected() override;

        int selectedPageOrder() const override;

        void selectPageOrder(int option) override;

        std::vector<PageOrderOption> pageOrderOptions() const override;

        void performRelinking(const AbstractRelinker& relinker) override;

        void preUpdateUI(FilterUiInterface* ui, const PageId& page_id) override;

        QDomElement saveSettings(const ProjectWriter& writer, QDomDocument& doc) const override;

        void loadSettings(const ProjectReader& reader, const QDomElement& filters_el) override;

        void loadDefaultSettings(const PageId& page_id) override;

        void setContentBox(const PageId& page_id, const ImageTransformation& xform, const QRectF& content_rect);

        void invalidateContentBox(const PageId& page_id);

        bool checkReadyForOutput(const ProjectPages& pages, const PageId* ignore = nullptr);

        intrusive_ptr<Task> createTask(const PageId& page_id,
                                       intrusive_ptr<output::Task> next_task,
                                       bool batch,
                                       bool debug);

        intrusive_ptr<CacheDrivenTask> createCacheDrivenTask(intrusive_ptr<output::CacheDrivenTask> next_task);

        OptionsWidget* optionsWidget();

    private:
        void writePageSettings(QDomDocument& doc, QDomElement& filter_el, const PageId& page_id, int numeric_id) const;

        intrusive_ptr<ProjectPages> m_ptrPages;
        intrusive_ptr<Settings> m_ptrSettings;
        SafeDeletingQObjectPtr<OptionsWidget> m_ptrOptionsWidget;
        std::vector<PageOrderOption> m_pageOrderOptions;
        int m_selectedPageOrder;
    };
}  // namespace page_layout
#endif  // ifndef PAGE_LAYOUT_FILTER_H_
