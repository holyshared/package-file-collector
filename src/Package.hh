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

use \ReflectionClass;
use \ReflectionException;

final class Package implements FromOptions<PackageOptions>
{

    private PackageNamespace $namespace;
    private DirectoryPath $packageDirectory;

    public function __construct(
        PackageOptions $options
    )
    {
        $this->namespace = (string) $options['namespace'];
        $this->packageDirectory = realpath($options['packageDirectory']);
    }

    <<__Memoize>>
    public function getNamespace() : PackageNamespace
    {
        $atoms = explode('\\', $this->namespace);
        $atoms = (new Vector($atoms))->filter((string $atom) ==> {
            return trim($atom) !== '';
        });
        return implode('\\', $atoms);
    }

    public function getPackageDirectory() : DirectoryPath
    {
        return $this->packageDirectory;
    }

    public function sources(Matcher<SourceFile> $matcher = new AnyMatcher()) : StreamObject<SourceFile>
    {
        $collector = new FileCollector($this->getPackageDirectory());
        return $collector->collect($matcher);
    }

    public function classes(Matcher<ClassObject> $matcher = new AnyMatcher()) : StreamObject<ClassObject>
    {
        $middleware = ClassTransformer::fromOptions(shape(
            'namespace' => $this->getNamespace(),
            'packageDirectory' => $this->getPackageDirectory()
        ));
        return $this->sources()->pipeTo($middleware)->select($matcher);
    }

    public static function fromOptions(PackageOptions $options) : this
    {
        return new static($options);
    }

}
