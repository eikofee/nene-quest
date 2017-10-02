sfml = []
sfml += dependency('sfml-graphics')
sfml += dependency('sfml-window')
sfml += dependency('sfml-system')
sfml += dependency('sfml-audio')

src = [
  'arrow.cpp', 'background.cpp', 'boar.cpp', 'bonus.cpp',
  'bonusHp.cpp', 'breakableObject.cpp', 'bridgePit.cpp',
  'customMap.cpp', 'dragon.cpp', 'enemy.cpp', 'entity.cpp',
  'flame.cpp', 'game.cpp', 'gameover.cpp', 'itemWeapon.cpp',
  'levelManager.cpp', 'levelParser.cpp', 'lifebar.cpp', 'main.cpp',
  'menu.cpp', 'parserCommand.cpp', 'parserFunction.cpp', 'player.cpp',
  'projectile.cpp', 'randomCloud.cpp', 'randomMountain.cpp',
  'weapon.cpp', 'weaponType.cpp', 'world.cpp'
]

executable('nene-quest', src, dependencies : sfml,
           gui_app : true, install : true)
