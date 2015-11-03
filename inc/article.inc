<?php
/**
 * @file
 * Migration of articles.
 */

/**
 * Class ArticleJsonMigration.
 */
class ArticleJsonMigration extends Migration {
  protected $amenties;
  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $fields = array(
      'article_id',
      'title',
      'text',
      'tag',
      'published',
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'article_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Unique ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $reader = array('reader_class' => 'MigrateJSONReader');
    $this->source = new MigrateSourceJSON(MIGRATION_JSON_EXAMPLE_ARTICLE_URL, 'article_id', $fields, $reader);
    $options = array(
      'language' => LANGUAGE_NONE,
    );
    // Content destination.
    $this->destination = new MigrateDestinationNode('article', $options);
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'text');
    $this->addFieldMapping('created', 'published');
    $this->addFieldMapping('field_tags', 'tag')->separator(',');
    $this->addFieldMapping('field_tags:create_term')->defaultValue(1);
    $this->addFieldMapping('field_image', 'picture');
    $this->addFieldMapping('field_image:source_dir')
       ->defaultValue(MIGRATION_JSON_EXAMPLE_ARTICLE_IMAGES_JSON_URL);
    $this->addFieldMapping('field_image:preserve_files')
       ->defaultValue(TRUE);
    $this->addFieldMapping('uid', 'account_id')
         ->sourceMigration('UserJsonMigration')
         ->defaultValue(1);
  }

}
