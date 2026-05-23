blueprints = custom_target('blueprints',
  input: files(
    'kissaki-window.blp',
    'shortcuts-dialog.blp',
  ),
  output: '.',
  command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

kissaki_sources = [
  'main.c',
  'kissaki-application.c',
  'kissaki-window.c',
  'kissaki-core.c',
]

kissaki_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
  dependency('gtksourceview-5'),
]

kissaki_sources += gnome.compile_resources('kissaki-resources',
  'kissaki.gresource.xml',
  dependencies: blueprints,
    source_dir: [
        meson.current_build_dir(),
        meson.current_source_dir(),
        meson.project_source_root() / 'data',
        meson.project_build_root() / 'data'
    ],
  c_name: 'kissaki'
)

executable('kissaki', kissaki_sources,
  dependencies: kissaki_deps,
       install: true,
)
