class UpdateDesignsForPaperclip < ActiveRecord::Migration
  def self.up
		rename_column :designs, :filename, :photo_file_name
		rename_column :designs, :content_type, :photo_content_type
		rename_column :designs, :size, :photo_file_size
		
		add_column :designs, :photo_updated_at, :timestamp
  end

  def self.down
		rename_column :designs, :photo_file_name, :filename
		rename_column :designs, :photo_content_type, :content_type
		rename_column :designs, :photo_file_size, :size
		
		drop_column :designs, :photo_updated_at
  end
end
