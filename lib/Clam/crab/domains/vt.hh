
#pragma once

#include <crab/domains/vt_domain.hpp>
#include "crab_defs.hh"

namespace clam {
	using BASE(vt_domain_t) = crab::domains::vt_domain<number_t, region_subdom_varname_t>;
	using vt_domain_t = RGN_FUN(ARRAY_FUN(BOOL_NUM(BASE(vt_domain_t))));
} // end namespace clam
