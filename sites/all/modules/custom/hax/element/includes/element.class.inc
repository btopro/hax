<?php

/**
 * @file
 * Element class.
 */

/**
 * The class used for element entities.
 */
class Element extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'element');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return array('path' => 'element/' . $this->element_id);
  }
}

/**
 * The class used for Element type entities.
 */
class ElementType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'element_type');
  }
}
