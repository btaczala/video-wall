#ifndef IFONT_H_KKMSA2F9
#define IFONT_H_KKMSA2F9

#include <memory>

namespace mars {
namespace windowing {

struct ITexture;

struct IFont {
    virtual ~IFont() = default;

    virtual std::unique_ptr<ITexture> renderText(const std::string& text) noexcept = 0;
};
}
}

#endif /* end of include guard: IFONT_H_KKMSA2F9 */
