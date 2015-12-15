<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package
{
    type DirectoryPath = string;
    type PackageNamespace = string;
    type SourceFileName = string;
    type ClassName = string;
    type PackageOptions = shape(
        'namespace' => PackageNamespace,
        'packageDirectory' => DirectoryPath
    );

    type StreamSource<T> = KeyedIterator<int, T>;

    type ClassMatcher = Matcher<ClassObject>;
};
