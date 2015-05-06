task :genimage do

  SKETCH_FILE = "Artwork/RailDesigner.sketch"
  IMAGE_DIR = "Resources/images/retina"

  if %x{which sketchtool}.empty?
    puts 'You must install sketchtool first'
    puts 'http://bohemiancoding.com/sketch/tool/'
    exit
  end
  sh "sketchtool export slices #{SKETCH_FILE} --output=#{IMAGE_DIR}"
end
