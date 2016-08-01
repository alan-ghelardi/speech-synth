fs = require 'fs-extra'
path = require 'path'
spawn = require '../libs/spawn-wrapper'

module.exports = (grunt) ->
  includeDir = path.join(process.cwd(), 'src', 'add-on', 'include')
  espeakSources = path.join(includeDir, 'espeak-ng', 'src')
  windowsDir = path.join(espeakSources, 'windows')

  buildOnWindows = (done) ->
    copyPcaudiolib()
    vsProjectFile = path.join(windowsDir, 'libespeak-ng.vcxproj')
    args = [ vsProjectFile, '/Property:Configuration=Release', '/Property:Platform=X64' ]
    msbuild = spawn('msbuild', args)
    msbuild.on('exit', (code) ->
      if code isnt 0
        grunt.log.errorlns('Failed to compile espeak-ng project')
        done(false)
      else
        copyWindowsArtifacts()
        cleanPcaudiolibFolder()
        done())

  copyPcaudiolib = ->
    pcaudiolibSource = path.join(includeDir, 'pcaudiolib')
    pcaudiolibTarget = path.join(espeakSources, 'pcaudiolib')
    grunt.log.writeln("Copying the pcaudiolib project from #{pcaudiolibSource} to #{pcaudiolibTarget}")
    fs.copySync(pcaudiolibSource, pcaudiolibTarget)

  copyWindowsArtifacts = ->
    releaseDir = path.join(windowsDir, 'X64', 'Release')
    copyEspeakLib(releaseDir)
    copyEspeakDLL(releaseDir)
    fs.removeSync(path.dirname(releaseDir))

  copyEspeakLib = (releaseDir) ->
    espeakLib = 'libespeak-ng.lib'
    espeakLibSrc = path.join(releaseDir, espeakLib)
    espeakLibDest = path.join(process.cwd(), 'build', espeakLib)
    grunt.log.writeln("Copying from #{espeakLibSrc} to #{espeakLibDest}")
    fs.copySync(espeakLibSrc, espeakLibDest)

  copyEspeakDLL = (releaseDir) ->
    espeakDLL = 'libespeak-ng.dll'
    espeakDLLSrc = path.join(releaseDir, espeakDLL)
    espeakDLLDest = path.join(process.cwd(), 'dist', 'win32', espeakDLL)
    grunt.log.writeln("Copying from #{espeakDLLSrc} to #{espeakDLLDest}")
    fs.copySync(espeakDLLSrc, espeakDLLDest)

  cleanPcaudiolibFolder = ->
    pcaudiolibTarget = path.join(espeakSources, 'pcaudiolib')
    fs.removeSync(pcaudiolibTarget)

  grunt.registerTask('build-espeak-ng', 'Builds the espeak-ng project', ->
    done = @async()
    buildOnWindows(done))
