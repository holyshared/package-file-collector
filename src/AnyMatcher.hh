<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package;

final class AnyMatcher<T> implements Matcher<T>
{
    public function matches(T $item) : bool
    {
        return true;
    }
}
