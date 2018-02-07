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

#ifndef SELECT_CONTENT_SETTINGS_H_
#define SELECT_CONTENT_SETTINGS_H_

#include "ref_countable.h"
#include "NonCopyable.h"
#include "PageId.h"
#include "Params.h"
#include <QMutex>
#include <memory>
#include <map>

class AbstractRelinker;

namespace select_content {
    class Settings : public ref_countable {
    DECLARE_NON_COPYABLE(Settings)

    public:
        Settings();

        ~Settings() override;

        void clear();

        void performRelinking(const AbstractRelinker& relinker);

        void updateDeviation();

        void setPageParams(const PageId& page_id, const Params& params);

        void clearPageParams(const PageId& page_id);

        std::unique_ptr<Params> getPageParams(const PageId& page_id) const;

        bool isParamsNull(const PageId& page_id) const;

        double maxDeviation() const;

        void setMaxDeviation(double md);

        QSizeF pageDetectionBox() const;

        void setPageDetectionBox(QSizeF size);

        double pageDetectionTolerance() const;

        void setPageDetectionTolerance(double tolerance);

        double avg() const;

        void setAvg(double a);

        double std() const;

        void setStd(double s);

    private:
        typedef std::map<PageId, Params> PageParams;

        mutable QMutex m_mutex;
        PageParams m_pageParams;
        double m_avg;
        double m_sigma;
        double m_maxDeviation;
        QSizeF m_pageDetectionBox;
        double m_pageDetectionTolerance;
    };
}  // namespace select_content
#endif // ifndef SELECT_CONTENT_SETTINGS_H_
